#pragma once
#ifndef PLANE_H
#define PLANE_H
#include "Primitive.h"
class Plane :
	public Primitive
{
public:
	Plane();
	Plane(glm::vec3 pos, Material* mat, glm::vec3 norm) : Primitive(pos, mat), normal(norm) {};
	
	~Plane();

	bool Intersection(Ray* ray);

private:
	glm::vec3 normal;
};

#endif //PLANE_H