#pragma once
#include "Primitive.h"
class Sphere :
	public Primitive
{
public:
	Sphere();
	Sphere(glm::vec3 position, Material* mat, float radi) : Primitive(position, mat), radius(radi) {};
	~Sphere();

	bool Intersection(Ray* ray);

private:

	float radius;
};

