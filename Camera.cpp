#include "Camera.h"
#include "glm\gtc\random.hpp"
#include "Renderer.h"

Camera::Camera(glm::vec3 origin, glm::vec3 look_at, glm::vec3 world_up, float vertical_fov, float near_plane_distance, unsigned int rays_per_pixel)
	: _origin(origin), _rays_per_pixel(rays_per_pixel), _near_plane_distance(near_plane_distance), _vertical_fov(vertical_fov) {
	//Rays per pixel is always a power-of-two to enable supersampling
	double base_two = glm::log2(static_cast<double>(_rays_per_pixel));
	double nearest_pot = glm::pow(2.0, glm::ceil(base_two));
	_rays_per_pixel = static_cast<unsigned int>(nearest_pot);

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

	Renderer renderer;
	for (unsigned int y = 0; y < buffer.get_height(); ++y) {
		for (unsigned int x = 0 ; x < buffer.get_width(); ++x) {
			//Compute color for each ray and take the average
			Ray ray;
			glm::vec3 final_color(0);
			for (unsigned int r = 0; r < _rays_per_pixel; ++r) {
				//TODO: Set different coordinates for each ray per pixel and give random offset within that subpixel
				set_ray_direction(ray, (float)x, (float)y);

				final_color += renderer.compute_light(scene, ray, _origin);
			}
			final_color /= _rays_per_pixel;
			//Set to pixel buffer
			buffer._pixels.at(y).at(x).set_rgb_color_value(final_color);
		}
	}
}

void Camera::set_ray_direction(Ray &ray, float x, float y) {
	ray._origin = glm::vec3(_origin);
	ray._direction = glm::normalize((_near_plane_bot_left + _right * x * _pixel_width + _up * y * _pixel_height) - _origin);
}