#include "Box.h"


Box::Box()
{
}


Box::~Box()
{
}

bool Box::Intersection(Ray* ray)
{
	float txmin, txmax, tymin, tymax, tzmin, tzmax;
	if (ray->inv_direction.x >= 0)
	{
		txmin = (min.x - ray->origin.x) * ray->inv_direction.x;
		txmax = (max.x - ray->origin.x) * ray->inv_direction.x;
	}
	else
	{
		txmin = (max.x - ray->origin.x) * ray->inv_direction.x;
		txmax = (max.x - ray->origin.x) * ray->inv_direction.x;
	}

	if (ray->inv_direction.y >= 0)
	{
		tymin = (min.y - ray->origin.y) * ray->inv_direction.y;
		tymax = (max.y- ray->origin.y) * ray->inv_direction.y;
	}
	else
	{
		tymin = (max.y - ray->origin.y) * ray->inv_direction.y;
		tymax = (max.y - ray->origin.y) * ray->inv_direction.y;
	}

	if (ray->inv_direction.z >= 0)
	{
		tzmin = (min.z - ray->origin.z) * ray->inv_direction.z;
		tzmax = (max.z - ray->origin.z) * ray->inv_direction.z;
	}
	else
	{
		tzmin = (max.z - ray->origin.z) * ray->inv_direction.z;
		tzmax = (max.z - ray->origin.z) * ray->inv_direction.z;
	}
	/* following might not be needed
	txmin = glm::min(txmin, txmax);
	txmax = glm::max(txmin, txmax);

	tymin = glm::min(tymin, tymax);
	tymax = glm::max(tymin, tymax);

	tzmin = glm::min(tzmin, tzmax);
	tzmax = glm::max(tzmin, tzmax);
	*/
	float tmin = glm::min(txmin, glm::min(tymin, tzmin));
	float tmax = glm::max(txmax, glm::max(tymax, tzmax));

	return tmax >= tmin;
}
