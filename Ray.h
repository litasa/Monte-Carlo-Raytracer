#pragma once
#include "glm\glm.hpp"
///A ray has an origin and a direction as well as importance.
class Ray {
public:
	Ray() = default;
	Ray(glm::vec3 origin, glm::vec3 direction) : _origin(origin) {
		_direction = glm::normalize(direction);
		//Save the inverse direction, only need to be computed once
		_inv_direction.x = 1.0f / _direction.x;
		_inv_direction.y = 1.0f / _direction.y;
		_inv_direction.z = 1.0f / _direction.z;
	}
	glm::vec3 _origin;
	glm::vec3 _direction;
	glm::vec3 _inv_direction;
	//For ray tracing
	float _importance;
};