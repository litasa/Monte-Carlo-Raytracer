#include "Camera.h"
#include <algorithm>
#include "glm\gtc\random.hpp"
#include "Renderer.h"
#ifndef SHADOW_RAYS
#define SHADOW_RAYS 10
#endif
#ifndef RECURSION_DEPTH
#define RECURSION_DEPTH 5
#endif

Camera::Camera(glm::vec3 origin, glm::vec3 look_at, glm::vec3 world_up, float vertical_fov, float near_plane_distance, unsigned int rays_per_pixel)
	: _origin(origin), _rays_per_pixel(rays_per_pixel), _near_plane_distance(near_plane_distance), _vertical_fov(vertical_fov) {
	//Rays per pixel is always a power-of-two to enable supersampling
	double base_two = glm::log2(static_cast<double>(_rays_per_pixel));
	double nearest_pot = glm::pow(2.0, glm::ceil(base_two));
	_rays_per_pixel = static_cast<unsigned int>(nearest_pot);
	//Always need at least 1 ray per pixel
	if (_rays_per_pixel == 0) {
		_rays_per_pixel = 1;
	}
	//Create orthonormal base
	_direction = glm::normalize(look_at - origin);
	_right = glm::cross(world_up, _direction);
	_up = glm::cross(_direction, _right);
};

void Camera::render_scene(const Scene &scene, PixelBuffer &buffer) {
	_width = (float)buffer.get_width();
	_height = (float)buffer.get_height();
	_aspect_ratio = _width / _height;
	//Calculate near plane
	_near_plane_height = 2.0f * _near_plane_distance * glm::tan(glm::radians(_vertical_fov * 0.5f));
	_near_plane_width = _near_plane_height * _aspect_ratio;
	_near_plane_center = _origin + _direction * _near_plane_distance;
	_near_plane_bot_left = _near_plane_center - _up * _near_plane_height * 0.5f - _right * _near_plane_width * 0.5f;
	//Use for supersampling and stepping
	_pixel_width = _near_plane_width / _width;
	_pixel_height = _near_plane_height / _height;
	//Cast the first rays from the camera using multithreading
	concurrent_initial_raycast(scene, buffer);
}

void Camera::concurrent_initial_raycast(const Scene &scene, PixelBuffer &buffer) {
	//Find the number of hardware threads and get the image work area for each tile
	unsigned int hw_threads = std::thread::hardware_concurrency() / 2;
	unsigned int tile_width = buffer.get_width() / hw_threads;
	unsigned int tile_height = buffer.get_height() / hw_threads;
	//For each tile, start a new thread
	std::vector<std::thread> threads;
	for (unsigned int y = 0; y < hw_threads; ++y) {
		for (unsigned int x = 0; x < hw_threads; ++x) {
			threads.push_back(std::thread(&Camera::concurrent_help_func, this, std::ref(scene), std::ref(buffer), x, y, tile_width, tile_height));
		}
	}
	//Join all threads
	std::for_each(threads.begin(), threads.end(), [](std::thread &t) { t.join(); });
}

void Camera::concurrent_help_func(const Scene &scene, PixelBuffer &buffer, unsigned int x_id, unsigned y_id, unsigned int tile_width, unsigned int tile_height) {
	//lock so we use use same random sample for each thread
	mutex.lock();
	std::srand((unsigned int)std::time(0));
	mutex.unlock();
	Ray ray;
	ray._importance = 1.0;
	Renderer renderer(scene, RECURSION_DEPTH, SHADOW_RAYS);
	float color_ratio = 1.0f / _rays_per_pixel;
	unsigned int sub_pixel_count = _rays_per_pixel / 2;
	float sub_pixel_step = _pixel_width / sub_pixel_count;

	for (unsigned int y = y_id * tile_height; y < (y_id + 1) * tile_height; ++y) {
		for (unsigned int x = x_id * tile_width; x < (x_id + 1) * tile_width; ++x) {
			glm::vec3 final_color;
			//Compute light for each ray in a pixel
			if (sub_pixel_count != 0) {
				for (unsigned int y_ray = 0; y_ray < sub_pixel_count; ++y_ray) {
					for (unsigned int x_ray = 0; x_ray < sub_pixel_count; ++x_ray) {
						set_jittered_ray_direction(ray, static_cast<float>(x), static_cast<float>(y), sub_pixel_step, 1.0f);
						final_color += renderer.radiance(ray);
						final_color /= sub_pixel_count;
					}
				}
			}
			else {
				set_ray_direction(ray, static_cast<float>(x), static_cast<float>(y));
				final_color += renderer.radiance(ray);
			}
			final_color.x = glm::clamp(final_color.x, 0.0f, 1.0f);
			final_color.y = glm::clamp(final_color.y, 0.0f, 1.0f);
			final_color.z = glm::clamp(final_color.z, 0.0f, 1.0f);

			//Synchronize buffer write access
			mutex.lock();
			buffer._pixels.at(y).at(x).set_rgb_color_value(final_color);
			mutex.unlock();
		}
	}
	std::cout << "\nNumber of direct rays: " << renderer.get_num_direct_rays() << std::endl;
	std::cout << "Number of indirect rays: " << renderer.get_num_indirect_rays() << std::endl;
}

void Camera::set_ray_direction(Ray &ray, float x, float y) {
	//Rays are sent from the camera origin in the direction of a pixel position (in view coordinates)
	ray._importance = 1.0f;
	ray._origin = glm::vec3(_origin);
	ray._direction = glm::normalize((_near_plane_bot_left + _right * x * _pixel_width + _up * y * _pixel_height) - _origin);
}

void Camera::set_jittered_ray_direction(Ray &ray, float x, float y, float sub_pixel_size, float amount) {
	//Rays are sent from the camera origin in the direction of a pixel position (in view coordinates)
	ray._importance = 1.0f;
	ray._origin = glm::vec3(_origin + glm::linearRand(0.0f, amount * sub_pixel_size) * _up + glm::linearRand(0.0f, amount * sub_pixel_size) * _right);
	ray._direction = glm::normalize((_near_plane_bot_left + _right * x * _pixel_width + _up * y * _pixel_height) - _origin);
}