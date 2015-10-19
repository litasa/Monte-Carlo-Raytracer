#pragma once
#include "BRDF.h"
///This is a derived class of the abstract base class BRDF.
///It has a 100% probability of light traveling in any direction on the hemisphere, this is mainly used for light sources
class DummyBRDF : public BRDF {
public:
	DummyBRDF() : BRDF() {}
	//Regardless of input just return 1
	glm::vec3 get(const glm::vec3 &surface_normal, const glm::vec3 &in, const glm::vec3 &out) override {
		return glm::vec3(1);
	}
	//This is just a dummy BRDF
	BRDFType get_type() override { return BRDFType::DUMMY; }
};