#pragma once
#ifndef RAY_H
#define RAY_H

#include "glm\glm.hpp"

//originID is the spawning triangle
//refraktiveIndex is for when we need to go into materia
class Ray
{
public:
	Ray()
	{
		refraktiveIndex = 1.0; //air
		originID = -1;
	};
	Ray(glm::vec3 orig, glm::vec3 direc, float refID = 1.0, int oriID = -1)
	{
		origin = orig;
		direction = direc;
		refraktiveIndex = refID;
		originID = oriID;
	}
	//~Ray(){};

	glm::vec3 origin;
	glm::vec3 direction;

	int originID;
	float refraktiveIndex;

};

#endif