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

	virtual glm::vec3 Intersection(Ray* ray) = 0;
	virtual glm::vec3 GetNormalAt(glm::vec3 pos) = 0;

	glm::vec3 position;
	Material* material;
};

#endif