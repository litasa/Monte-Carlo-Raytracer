#include "Plane.h"


Plane::Plane()
{
}


Plane::~Plane()
{
}

bool Plane::Intersection(Ray* ray)
{
	float denom = glm::dot(normal, ray->direction);

	if (denom > 1e-6) //if denom is small then ray and plane is parallell
	{
		glm::vec3 posOrg = position - ray->origin;
		float t = glm::dot(posOrg, normal);
		return (t >= 0);
	}
	return false;
}
