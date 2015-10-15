#pragma once
#include "glm\glm.hpp"
class Material
{
public:
	virtual ~Material() {}
	virtual glm::vec3 get_color() {
		return _color;
	}

	virtual glm::vec3 get_emitted() {
		return _emitted;
	}

	float _refractive;
	float _reflective;
protected:
	Material() = default;
	glm::vec3 _color;
	glm::vec3 _emitted;
};

