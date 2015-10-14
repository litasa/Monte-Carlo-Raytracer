#pragma once
#include "Material.h"
class LightMaterial : public Material {
public:
	LightMaterial(glm::vec3 color) : Material() {
		_reflective = 0.0f;
		_refractive = 0.0f;
		_light = true;
		_color = color;
	}
};