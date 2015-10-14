#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\constants.hpp"
#include "Material.h"
class DiffuseMaterial : public Material {
public:
	DiffuseMaterial(glm::vec3 color) : Material() {
		_color = color;
		_reflective = 1.0f / glm::pi<float>();
		_refractive = 0.0;
		_light = false;
	}
};