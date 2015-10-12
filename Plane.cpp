#include "Plane.h"
#include <iostream>

Plane::Plane()
{
}


Plane::~Plane()
{
}

glm::vec3 Plane::Intersection(Ray* ray)
{
	float D = (normal.x*ray->origin.x + normal.y*ray->origin.y + normal.z*ray->origin.z + d) / glm::length(normal);
	if (D > 0 && glm::dot(ray->direction,normal) > 0)
	{
		return glm::vec3(-100);
	}
	else if (D < 0 && glm::dot(ray->direction, normal) < 0)
	{
		return glm::vec3(-100);
	}
	float t = -(glm::dot(ray->origin, normal) + d) / (glm::dot(ray->direction, normal));
	std::cout << "t: " << t << std::endl;
	glm::vec3 hitP = ray->origin + t*ray->direction;
	return hitP;
}

glm::vec3 Plane::GetNormalAt(glm::vec3 hitPos)
{
	return normal;
}