#pragma once
#ifndef RAY_H
#define RAY_H

#include "glm\glm.hpp"

//originID is the spawning triangle
//refraktiveIndex is for when we need to go into materia
class Ray
{
public:
	Ray() {};
	Ray(glm::vec3 orig, glm::vec3 direc) : origin(orig), direction(direc)
	{
		inv_direction.x = 1 / direc.x;
		inv_direction.y = 1 / direc.y;
		inv_direction.z = 1 / direc.z;
		parent = nullptr;
		reflected_child = nullptr;
		refracted_child = nullptr;
	}

	~Ray() { delete parent; delete reflected_child; delete reflected_child; };

	glm::vec3 origin;
	glm::vec3 direction;
	glm::vec3 inv_direction;

	Ray* parent;
	Ray* refracted_child;
	Ray* reflected_child;

	float importance;

};

#endif