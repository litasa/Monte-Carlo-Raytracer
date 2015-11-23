#pragma once
#include "glm\gtc\constants.hpp"
#include "BRDF.h"
///This is a derived class of the abstract base class BRDF, it is a perfect diffuse reflector. 
///This means the probability for light being reflected on the surface is uniformly distributed on the hemisphere.
class ReflectionBRDF : public BRDF {
public:
	ReflectionBRDF() : BRDF() {}
	//Regardless of the input we return some constant over the normalization pi
	glm::vec3 get(const glm::vec3 &surface_normal, const glm::vec3 &light_dir, const glm::vec3 &view_dir) override {
		return glm::vec3(glm::dot(surface_normal, light_dir) * _rho / glm::pi<float>());
	}
	//This is a diffuse BRDF type
	BRDFType get_type() override { return BRDFType::REFLECT; }
private:
	const float _rho = 1.0f; //From 0..1
};