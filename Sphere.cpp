#include "Sphere.h"
#include "glm\gtc\random.hpp"
#include <utility>

glm::vec3 Sphere::intersection(const Ray &ray) {
	glm::vec3 L = _position - ray._origin;
	float tca = glm::dot(L, ray._direction);
	float d2 = glm::dot(L, L) - tca * tca;
	//Intersections "behind" origin not interesting
	if (tca < 0 || d2 > _radius_squared) {
		return _no_intersection;
	}

	float thc = sqrt(_radius_squared - d2);
	float t0 = tca - thc;
	float t1 = tca + thc;
	if (t0 > t1) {
		std::swap(t0, t1);
	}

	if (t0 < 0) {
		t0 = t1; //If t0 is negative use t1 instead
		if (t0 < 0) {
			return _no_intersection; //Both t1 and t0 is negative
		}
	}

	//Find closest point to the ray origin
	if (t0 < t1) {
		return (ray._origin + t0 * ray._direction);
	}
	else {
		return (ray._origin + t1 * ray._direction);
	}
}

glm::vec3 Sphere::get_normal_at(const glm::vec3 &hit_point) {
	return glm::normalize(hit_point - _position);
}

float Sphere::area() {
	return _area;
}

float Sphere::uniform_pdf() {
	return _inverse_area;
}

glm::vec3 Sphere::uniform_random_sample() {
	return glm::sphericalRand(_radius);
}


void Sphere::uniform_random_sample(int nr_samples, std::vector<glm::vec3>& samples) {
	for (int i = 0; i < nr_samples; ++i) {
		samples.push_back(uniform_random_sample());
	}
}
