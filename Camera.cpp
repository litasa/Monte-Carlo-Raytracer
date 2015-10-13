#include "Camera.h"
#include "glm\gtc\random.hpp"
#include "Renderer.h"

Camera::Camera(glm::vec3 origin, glm::vec3 direction, glm::vec3 right, glm::vec3 up, unsigned int rays_per_pixel) : _origin(origin), _direction(direction), _right(right), _up(up) {
	//Rays per pixel is always a power-of-two to enable supersampling
	double base_two = glm::log2(static_cast<double>(_rays_per_pixel));
	double nearest_pot = glm::pow(2.0, glm::ceil(base_two));
	_rays_per_pixel = static_cast<unsigned int>(nearest_pot);

	if (_rays_per_pixel == 0) {
		_rays_per_pixel = 1;
	}

//	_direction = glm::cross(_right, _up);
};

void Camera::render_scene(const Scene &scene, PixelBuffer &buffer) {

	_half_width = (float)buffer.get_width() * 0.5f;
	_half_height = (float)buffer.get_height() * 0.5f;
	_width = (float)buffer.get_width();
	_height = (float)buffer.get_height();
	_aspect_ratio = _width / _height;

	Renderer renderer;
	for (unsigned int y = 0; y < buffer.get_height(); ++y) {
		for (unsigned int x = 0 ; x < buffer.get_width(); ++x) {
			//Compute color for each ray and take the average
			Ray ray;
			glm::vec3 final_color(0);
			for (unsigned int r = 0; r < _rays_per_pixel; ++r) {
				//Convert our raster coordinates to NDC
				//TODO: Set different coordinates for each ray per pixel and give random offset within that subpixel
				glm::vec2 raster_coordinate(x, y);
				glm::vec2 normalized_device_coordinate(normalize_coordinate(raster_coordinate));
				set_ray_direction(ray, normalized_device_coordinate.x, normalized_device_coordinate.y);
				final_color += renderer.compute_light(scene, ray);
			}
			final_color /= _rays_per_pixel;
			//Set to pixel buffer
			buffer._pixels.at(y).at(x).set_rgb_color_value(final_color);
		}
	}
}

glm::vec2 Camera::normalize_coordinate(const glm::vec2 &coordinate) {
	glm::vec2 normalized_device_coordinate; 
	normalized_device_coordinate.x = _aspect_ratio * (-_half_width + coordinate.x) / _width;
	normalized_device_coordinate.y = (-_half_height + coordinate.y) / _height;
	return normalized_device_coordinate;
}

void Camera::set_ray_direction(Ray &ray, float x, float y) {
	ray._origin = glm::vec3(_origin);
	ray._direction = glm::normalize(glm::vec3(x, y, _near_plane_distance));
}