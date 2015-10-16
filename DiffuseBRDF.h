#pragma once
#include "glm\gtc\constants.hpp"
#include "BRDF.h"
class DiffuseBRDF : public BRDF {
public:
	DiffuseBRDF() : BRDF() {}
	glm::vec3 get(const glm::vec3 &surface_normal, const glm::vec3 &in, const glm::vec3 &out) override {
		return glm::vec3(_rho / glm::pi<float>());
	}
private:
	const float _rho = 1.0f;
};