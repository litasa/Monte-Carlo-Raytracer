#pragma once
#include <memory>
#include "glm\glm.hpp"
class Ray : std::enable_shared_from_this<Ray>
{
public:
	Ray() = default;
	Ray(glm::vec3 origin, glm::vec3 direction) : _origin(origin)
	{
		_direction = glm::normalize(direction);
		_inv_direction.x = 1.0f / _direction.x;
		_inv_direction.y = 1.0f / _direction.y;
		_inv_direction.z = 1.0f / _direction.z;
	}

	glm::vec3 _origin;
	glm::vec3 _direction;
	glm::vec3 _inv_direction;

	std::shared_ptr<Ray> _parent;
	std::shared_ptr<Ray> _refracted_child;
	std::shared_ptr<Ray> _reflected_child;

	float _importance;
};