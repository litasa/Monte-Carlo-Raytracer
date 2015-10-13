#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "PixelBuffer.h"
#include "Scene.h"
///A camera is our eye that picks up light that's emitted from the scene.
class Camera {
public:
	Camera() = default;
	Camera(glm::vec3 origin, glm::vec3 direction, glm::vec3 right, glm::vec3 up, unsigned int rays_per_pixel);
	void set_origin(const glm::vec3 &origin) { _origin = origin; }
	void set_direction(const glm::vec3 &direction) { _direction = direction; }
	void set_right(const glm::vec3 &right) { _right = right; }
	void set_up(const glm::vec3 &up) { _up = up; }
	void render_scene(const Scene &scene, PixelBuffer &buffer);
	friend class PixelBuffer; //The camera has direct access to pixels in the pixel buffer
private:
	glm::vec3 _origin, _direction, _right, _up;
	float _near_plane_distance = 1.0f;
	float _width;
	float _height;
	float _aspect_ratio;
	float _half_width;
	float _half_height;
	unsigned int _rays_per_pixel;
	void set_ray_direction(Ray &ray, float x, float y);
	glm::vec2 normalize_coordinate(const glm::vec2 &coordinate);
};
