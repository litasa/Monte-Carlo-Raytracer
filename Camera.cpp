#include "Camera.h"
#include "glm\gtc\random.hpp"
#include "Renderer.h"

Camera::Camera(glm::vec3 origin, glm::vec3 direction, unsigned int rays_per_pixel) : _origin(origin), _direction(direction) {
	//Rays per pixel is always a power-of-two to enable supersampling
	double base_two = glm::log2(static_cast<double>(_rays_per_pixel));
	double nearest_pot = glm::pow(2.0, glm::ceil(base_two));
	_rays_per_pixel = static_cast<unsigned int>(nearest_pot);

	if (_rays_per_pixel == 0) {
		_rays_per_pixel = 1;
	}
};

void Camera::render_scene(const Scene &scene, PixelBuffer &buffer) {

	Renderer renderer;
	unsigned int y = 0, x = 0;
	for (unsigned int y = 0; y < buffer.get_height(); ++y) {
		for (unsigned int x = 0 ; x < buffer.get_width(); ++x) {
			//Compute color for each ray and take the average
			glm::vec3 final_color(0);
			for (unsigned int r = 0; r < _rays_per_pixel; ++r) {
				Ray ray;
				set_ray_direction(ray, x, y);
				final_color += renderer.compute_light(scene, ray);
			}
			final_color /= _rays_per_pixel;
			//Set to pixel buffer
			buffer._pixels.at(y).at(x).set_rgb_color_value(final_color);
		}
	}
}

void Camera::set_ray_direction(Ray &ray, int x, int y) {
	ray._direction = glm::normalize(glm::vec3(x, y, near_plane_distance));
}