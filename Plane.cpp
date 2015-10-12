#include "Plane.h"
#include <iostream>

glm::vec3 Plane::intersection(const Ray &ray)
{
	float D = (_normal.x*ray._origin.x + _normal.y*ray._origin.y + _normal.z*ray._origin.z + _d) / glm::length(_normal);
	if (D > 0 && glm::dot(ray._direction,_normal) > 0)
	{
		return _no_intersection;
	}
	else if (D < 0 && glm::dot(ray._direction, _normal) < 0)
	{
		return _no_intersection;
	}
	float t = -(glm::dot(ray._origin, _normal) + _d) / (glm::dot(ray._direction, _normal));
	//std::cout << "t: " << t << std::endl;
	glm::vec3 hit_point = ray._origin + t*ray._direction;
	return hit_point;
}

glm::vec3 Plane::get_normal_at(const glm::vec3 &hit_point)
{
	return _normal;
}