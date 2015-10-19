#pragma once
#include <mutex>
#include "glm\glm.hpp"
#include "Scene.h"
#include "Plane.h"
#include "Ray.h"
///Holds information about the nearest intersection, this is a convenient struct to have when dealing with radiance computation in the Renderer.
struct Intersection {
	Intersection() = default;
	Intersection(const glm::vec3 &radiance_direction) : _radiance_direction(radiance_direction) {}
	inline glm::vec3 get_normal() const { return _object->get_normal_at(_point); }
	float _distance;
	glm::vec3 _point;
	glm::vec3 _radiance_direction;
	std::shared_ptr<Primitive> _object;
};
///A renderer takes a scene and a ray computes the light for a pixel. It has complete information of the scene.
///It has methods for computing direct and indirect radiance for a point in the scene.
class Renderer {
public:
	Renderer(const Scene &scene, int max_recursion_depth, int shadow_rays) : _scene(scene), _max_recursion_depth(max_recursion_depth), _shadow_rays(shadow_rays) {
		//For debugging
		_num_direct_rays = 0;
		_num_indirect_rays = 0; 
		//These are constant when starting rendering, no need to compute all the time
		_light_count = static_cast<int>(_scene.get_light_sources().size());
		_light_probability = 1.0f / _light_count;
	}
	//Call this method to start estimated radiance computation
	glm::vec3 radiance(const Ray &ray);
	//Getters for debugging counters
	int get_num_direct_rays() const { return _num_direct_rays; }
	int get_num_indirect_rays() const  { return _num_indirect_rays; }
private:
	//Scene data
	const Scene _scene;
	//Debugging
	int _num_indirect_rays, _num_direct_rays;
	//Quality
	int _max_recursion_depth, _shadow_rays;
	const float _ray_epsilon = 0.000008f, _max_ray_distance = std::numeric_limits<float>().max();
	//Lights
	int _light_count;
	float _light_probability;
	//The rendering equation
	glm::vec3 compute_radiance(const Intersection &intersection, int depth);
	//The recursive integral in the rendering equation
	glm::vec3 compute_indirect_light(const Intersection &intersection, int depth);
	//Checks light visibility
	glm::vec3 compute_direct_light(const Intersection &intersection);
	//Computes a uniformly distributed random direction on the hemisphere
	glm::vec3 compute_diffuse_ray(const glm::vec3 normal);
	//Combined term for G and V
	float radiance_transfer(const Intersection &intersection, const std::shared_ptr<Primitive> &object, const glm::vec3 &sample_point);
	//Find the nearest intersection, sets the intersection data as out parameter
	void find_nearest(const Ray &ray, Intersection &intersection); 
	//Methods for direct illumination
	float geometry_term(const Intersection &intersection, const glm::vec3 &point, const glm::vec3 &normal); //Advanced Global Illumination. 2nd ed. page 43.
	float visibility_term(const Intersection &intersection, const glm::vec3 &point, const std::shared_ptr<Primitive> &object);
	//For debugging
	std::mutex mutex;
};

