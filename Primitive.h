#pragma once
#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Ray.h"
#include "Material.h"
class Primitive
{
public:
	Primitive();
	Primitive(glm::vec3 pos, Material* mat) : position(pos), material(mat) {};
	~Primitive();

	virtual bool Intersection(Ray* ray) = 0;

	glm::vec3 position;
	Material* material;
};

#endif