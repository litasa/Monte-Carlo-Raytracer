#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "PixelBuffer.h"
#include "Scene.h"
#include "RayCollection.h"
///A camera is our eye that picks up light that's emitted from the scene.
class Camera {
public:
	Camera() = default;
	Camera(glm::vec3 origin, glm::vec3 direction, unsigned int rays_per_pixel);
	void set_origin(const glm::vec3 &origin) { _origin = origin; }
	void set_direction(const glm::vec3 &direction) { _direction = direction; }
	void render_scene(const Scene &scene, PixelBuffer &buffer);
	friend class PixelBuffer; //The camera has direct access to pixels in the pixel buffer
private:
	glm::vec3 _origin, _direction;
	unsigned int _rays_per_pixel;
	std::vector<std::vector<RayCollection>> _rays;
};
