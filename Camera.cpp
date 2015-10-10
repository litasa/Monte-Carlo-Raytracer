#include "Camera.h"
#include "glm\gtc\random.hpp"

Camera::Camera(glm::vec3 origin, glm::vec3 direction, unsigned int rays_per_pixel) : _origin(origin), _direction(direction) {
	//Rays per pixel is always a power-of-two to enable supersampling
	double base_two = glm::log2(static_cast<double>(_rays_per_pixel));
	double nearest_pot = glm::pow(2.0, glm::ceil(base_two));
	_rays_per_pixel = static_cast<unsigned int>(nearest_pot);
};

void Camera::render_scene(const Scene &scene, PixelBuffer &buffer) {
	//Allocate rays per pixel
	_rays = std::vector<std::vector<RayCollection>>(buffer.get_height(), std::vector<RayCollection>(buffer.get_width(), RayCollection(_rays_per_pixel)));

	//TODO: Send each ray into scene and get intensity 
	unsigned int y = 0, x = 0;
	for (auto y_it = _rays.begin(); y_it != _rays.end(); ++y_it, ++y) {
		for (auto x_it = (*y_it).begin(); x_it != (*y_it).end(); ++x_it, ++x) {
			/*...*/
			//TODO: When ray has completed, calculate rgb value and set to pixel buffer
			glm::vec3 color = glm::vec3(glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0), glm::linearRand(0.0, 1.0)); //TODO: Remove this temporary
			buffer._pixels.at(y).at(x).set_rgb_color_value(color);
			/*...*/
		}
		//Reset row counter
		x = 0;
	}

	//All image data is now in the pixel buffer and thus it can be saved
}