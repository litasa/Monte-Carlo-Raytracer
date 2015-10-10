#pragma once
#ifndef BOX_H
#define BOX_H
#include "Primitive.h"
#include "Plane.h"

//based on http://people.csail.mit.edu/amy/papers/box-jgt.pdf
class Box :
	public Primitive
{
public:
	Box();
	Box(glm::vec3 pos, Material* mat, glm::vec3 minimum, glm::vec3 maximum) : 
		Primitive(pos, mat), min(minimum), max(maximum) {};
	~Box();

	bool Intersection(Ray* ray);

	glm::vec3 min;
	glm::vec3 max;

};

#endif //BOX_H