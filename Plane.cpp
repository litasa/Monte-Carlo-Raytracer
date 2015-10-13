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
	glm::vec3 hit_point = ray._origin + t*ray._direction;
	float hit_x = hit_point.x - _position.x;
	float hit_y = hit_point.y - _position.y;
	float hit_z = hit_point.z - _position.z;
	if (hit_x <= _size_x && hit_x >= -_size_x)
	{
		if (hit_y <= _size_y && hit_y >= -_size_y)
		{
			if (hit_z <= _size_z && hit_z >= -_size_z)
			{
				return hit_point;
			}
		}
	}
	return _no_intersection;
}

glm::vec3 Plane::get_normal_at(const glm::vec3 &hit_point)
{
	return _normal;
}