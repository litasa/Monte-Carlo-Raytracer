#pragma once
#include <vector>
#include "glm\glm.hpp"
#include "PixelBuffer.h"
#include "Scene.h"
///A camera is our eye that picks up light that's emitted from the scene.
class Camera {
public:
	Camera() = default;
	Camera(glm::vec3 origin, glm::vec3 look_at, glm::vec3 world_up, float vertical_fov, float near_plane_distance, unsigned int rays_per_pixel);
	void render_scene(const Scene &scene, PixelBuffer &buffer);
	friend class PixelBuffer; //The camera has direct access to pixels in the pixel buffer
private:
	glm::vec3 _origin, _direction, _right, _up;
	float _vertical_fov;
	float _near_plane_distance;
	float _width;
	float _height;
	float _aspect_ratio;
	float _near_plane_width;
	float _near_plane_height;
	float _pixel_width;
	float _pixel_height;
	glm::vec3 _near_plane_center;
	glm::vec3 _near_plane_bot_left;
	unsigned int _rays_per_pixel;
	void set_ray_direction(Ray &ray, float x, float y);
};
