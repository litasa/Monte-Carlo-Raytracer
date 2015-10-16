#include "Sphere.h"
#include <utility>

glm::vec3 Sphere::intersection(const Ray &ray)
{
	glm::vec3 L = _position - ray._origin;

	float tca = glm::dot(L, ray._direction);

	if (tca < 0) //intersections "behind" origin not interesting
	{
		return _no_intersection;
	}

	float d2 = glm::dot(L, L) - tca * tca;

	if (d2 > _radius*_radius)
	{
		return _no_intersection;
	}

	float thc = sqrt(_radius*_radius - d2);

	float t0 = tca - thc;
	float t1 = tca + thc;

	if (t0 > t1)
	{
		std::swap(t0, t1);
	}
	if (t0 < 0)
	{
		t0 = t1; //if t0 is negative use t1 instead
		if (t0 < 0)
		{
			return _no_intersection; //both t1 and t0 is negative
		}
	}
	//find closest point to the ray origin
	if (t0 < t1)
	{
		return (ray._origin + t0*ray._direction);
	}
	else
	{
		return (ray._origin + t1*ray._direction);
	}
}

glm::vec3 Sphere::get_normal_at(const glm::vec3 &hit_point)
{
	return glm::normalize(hit_point - _position);
}

float Sphere::area()
{
	return 0.0f;
}

float Sphere::uniform_pdf()
{
	return 0.0f;
}

glm::vec3 Sphere::uniform_random_sample() {
	return glm::vec3(0);
}

void Sphere::uniform_random_sample(int nr_samples, std::vector<glm::vec3>& samples)
{
}
