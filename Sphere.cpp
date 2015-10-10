#include "Sphere.h"
#include <utility>


Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}

bool Sphere::Intersection(Ray* ray)
{
	glm::vec3 L = position - ray->origin;

	float tca = glm::dot(L, ray->direction);

	if (tca < 0) //intersections "behind" origin not interesting
	{
		return false;
	}

	float d2 = glm::dot(L, L) - tca * tca;

	if (d2 > radius*radius)
	{
		return false;
	}

	float thc = sqrt(radius*radius - d2);

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
			return false; //both t1 and t0 is negative
		}
	}

	return true;
}