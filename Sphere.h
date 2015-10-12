#pragma once
#include "Primitive.h"
class Sphere :
	public Primitive
{
public:
	Sphere();
	Sphere(glm::vec3 position, Material* mat, float radi) : Primitive(position, mat), radius(radi) {};
	~Sphere();

	glm::vec3 Intersection(Ray* ray);
	glm::vec3 GetNormalAt(glm::vec3 hitPoint);

private:

	float radius;
};

