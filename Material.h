#pragma once
#include "glm\glm.hpp"
class Material
{
public:
	virtual ~Material() {}
	virtual glm::vec3 get_color() {
		return _color;
	}
protected:
	Material() = default;	
	glm::vec3 _color;
};

