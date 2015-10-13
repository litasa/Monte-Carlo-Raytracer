#pragma once
#include <vector>
#include <mutex>
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
	float _near_plane_distance, _near_plane_width, _near_plane_height;
	float _width, _height, _vertical_fov, _aspect_ratio;
	float _pixel_width, _pixel_height;
	glm::vec3 _near_plane_center, _near_plane_bot_left;
	unsigned int _rays_per_pixel;
	void set_ray_direction(Ray &ray, float x, float y);
	void set_jittered_ray_direction(Ray &ray, float x, float y, float sub_pixel_size, float amount);

	void concurrent_initial_raycast(const Scene &scene, PixelBuffer &buffer);
	void concurrent_help_func(const Scene &scene, PixelBuffer &buffer, unsigned int x_id, unsigned y_id, unsigned int tile_width, unsigned int tile_height);
	std::mutex mutex;
};
