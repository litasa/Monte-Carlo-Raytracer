#pragma once
#ifndef PLANE_H
#define PLANE_H
#include "Primitive.h"
class Plane :
	public Primitive
{
public:
	Plane();
	Plane(glm::vec3 pos, Material* mat, glm::vec3 norm) : Primitive(pos, mat), normal(norm) 
	{
		d = -norm.x*pos.x - norm.y*pos.y - norm.z*pos.z;
	};
	
	~Plane();

	glm::vec3 Intersection(Ray* ray);
	glm::vec3 GetNormalAt(glm::vec3 hitPoint);

private:
	float d;
	glm::vec3 normal;
};

#endif //PLANE_H