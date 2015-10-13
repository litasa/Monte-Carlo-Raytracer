#pragma once
#include "Material.h"
class DiffuseMaterial : public Material {
public:
	DiffuseMaterial(glm::vec3 color) : Material() {
		_color = color;
		_reflective = 0.0;
		_refractive = 0.0;
	}
};