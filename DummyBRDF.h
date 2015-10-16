#pragma once
#include "BRDF.h"
class DummyBRDF : public BRDF {
public:
	DummyBRDF() : BRDF() {}
	glm::vec3 get(const glm::vec3 &surface_normal, const glm::vec3 &in, const glm::vec3 &out) override {
		return glm::vec3(1);
	}
};