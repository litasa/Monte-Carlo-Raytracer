#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\random.hpp"
#include "Material.h"
///This is a derived class of the abstract base class BRDF, it is a perfect diffuse reflector. 
///This means the probability for light being reflected on the surface is uniformly distributed on the hemisphere.
class DiffuseMaterial : public Material {
public:
	DiffuseMaterial(const glm::vec3 &color, const glm::vec3 &emitted,
		const std::shared_ptr<BRDF> &reflect, const std::shared_ptr<BRDF> & refract) 
		:
		Material(color,emitted,reflect,refract) {}

	glm::vec3 get_ray_dir (const glm::vec3& surface_normal) {
	//Sample point on the hemisphere, just reverse it if it's on the "negative" hemisphere. Gives something like a uniform distribution.
		glm::vec3 random_dir = glm::sphericalRand(1.0f);
		return glm::dot(random_dir, surface_normal) > 0 ? random_dir : -random_dir;
	}
	//This is a diffuse BRDF type
	MATERIALType get_type() override { return MATERIALType::DIFFUSE; }
private:
	const float _rho = 1.0f; //From 0..1
};