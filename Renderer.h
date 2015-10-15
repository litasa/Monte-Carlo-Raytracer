#pragma once
#include "glm\glm.hpp"
#include "Scene.h"
#include "Plane.h"
#include "Ray.h"

///Holds information about the nearest intersection
struct Intersection {
	Intersection() = default;
	float distance;
	glm::vec3 point;
	glm::vec3 direction;
	std::shared_ptr<Primitive> object;
};

///A renderer takes a scene and a ray computes the light for a pixel
class Renderer {
public:
	Renderer() = default;
	Renderer(const Scene &scene, int recursion_depth, int shadow_rays) : _scene(scene), _recursion_depth(recursion_depth), _shadow_rays(shadow_rays) {}
	glm::vec3 radiance(const Ray &ray);
	
private:
	const Scene _scene;
	int _recursion_depth;
	int _shadow_rays;

	glm::vec3 compute_radiance(const Intersection &intersection);
	glm::vec3 compute_indirect_light(const Intersection &intersection);
	glm::vec3 compute_direct_light(const Intersection &intersection);
	float radiance_transfer(const Intersection &intersection, const std::shared_ptr<Primitive> &object, const glm::vec3 &sample_point);
	float probability_distribution(const std::shared_ptr<Primitive> &object, const glm::vec3 &point);
	float probability_distribution(const std::shared_ptr<Primitive> &object);
	//float radiance_transfer(const glm::vec3 &point_a, const glm::vec3 &point_b, const glm::vec3 &normal_a, const glm::vec3 &normal_b, const std::shared_ptr<Primitive> &object);
	void find_nearest(const Ray &ray, float &nearest_distance, glm::vec3 &nearest_point, std::shared_ptr<Primitive> &nearest_primitive);
	//The geometry term. Advanced Global Illumination page 43.
	float geometry_term(const glm::vec3 &point_a, const glm::vec3 &point_b, const glm::vec3 &normal_a, const glm::vec3 &normal_b);
	//The visibility term
	float visibility_term(const glm::vec3 &from_point, const glm::vec3 &direction, const std::shared_ptr<Primitive> &primitive);
};

