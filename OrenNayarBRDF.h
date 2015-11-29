#pragma once
#include "glm\gtc\constants.hpp"
#include "BRDF.h"
///This is a derived class of the abstract base class BRDF, it is a Oren-Nayar diffusor. 
///This means the probability for light being reflected on the surface is dependent on the gaussian standard
///deviation sigma.
class OrenNayarBRDF : public BRDF {
public:
	OrenNayarBRDF() : BRDF() {}
	//Oren Nayar diffuse. Models the surface as if it was composed of micro surfaces that scatter the light
	glm::vec3 get(const glm::vec3 &surface_normal, const glm::vec3 &light_dir, const glm::vec3 &view_dir) override {
	
		float alpha = glm::max(acos(glm::dot(light_dir, surface_normal)), acos(glm::dot(view_dir, surface_normal)));
		float beta = glm::min(acos(glm::dot(light_dir, surface_normal)), acos(glm::dot(view_dir, surface_normal)));

		float cosPhiDiff = glm::dot(light_dir - surface_normal*glm::dot(light_dir, surface_normal),
									view_dir - surface_normal*glm::dot(view_dir, surface_normal));

		float A = 1 - 0.5f*(_sigma2 / (_sigma2 + 0.33f));
		float B = 0.45f*(_sigma2 / (_sigma2 + 0.09f));
		float C = sin(alpha)*tan(beta);

		glm::vec3 res = glm::vec3(A + B*C*glm::max(0.0f, cosPhiDiff));
		glm::vec3 diffuse = glm::vec3(glm::dot(surface_normal, light_dir) * _rho / glm::pi<float>());

		return res*diffuse;
	}
	//This is a diffuse BRDF type
	BRDFType get_type() override { return BRDFType::ORENDIFFUSE; }
private:
	const float _rho = 1.0f; //From 0..1
	const float _sigma2 = 0.3f; //from 0..inf (it is squared)
};