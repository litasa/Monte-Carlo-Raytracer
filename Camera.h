#pragma once
#include <vector>
#include <mutex>
#include "glm\glm.hpp"
#include "PixelBuffer.h"
#include "Scene.h"
///A camera is our eye that picks up light that's emitted from the scene.
///It works in reverse though, we send rays from the camera through the lens, we trace these rays and check for light sources along its path.
class Camera {
public:
	Camera(glm::vec3 origin, glm::vec3 look_at, glm::vec3 world_up, float vertical_fov, float near_plane_distance, unsigned int rays_per_pixel, unsigned int shadow_rays, unsigned int max_recursion_depth);
	void render_scene(const Scene &scene, PixelBuffer &buffer);
private:
	//Camera parameters
	glm::vec3 _origin, _direction, _right, _up;
	float _width, _height, _vertical_fov, _aspect_ratio;
	//Near plane data
	float _pixel_width, _pixel_height;
	float _near_plane_distance, _near_plane_width, _near_plane_height;
	glm::vec3 _near_plane_center, _near_plane_bot_left;
	//Quality arguments
	unsigned int _rays_per_pixel, _shadow_rays, _max_recursion_depth;
	//Methods that returns a ray throught a pixel
	void set_ray_direction(Ray &ray, float x, float y);
	void set_jittered_ray_direction(Ray &ray, float x, float y, float sub_pixel_size, float amount);
	//Some members and helper functions for parallelizing the code 
	void concurrent_initial_raycast(const Scene &scene, PixelBuffer &buffer);
	void concurrent_help_func(const Scene &scene, PixelBuffer &buffer, unsigned int x_id, unsigned y_id, unsigned int tile_width, unsigned int tile_height);
	std::mutex mutex;
};
