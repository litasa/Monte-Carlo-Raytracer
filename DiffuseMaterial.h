#pragma once
#include "Material.h"
class DiffuseMaterial : public Material {
public:
	DiffuseMaterial(glm::vec3 color) : Material() {
		_color = color;
		_reflective = 0.31830988618f; // 1/pi lambertian reflector
		_refractive = 0.0;
	}
};