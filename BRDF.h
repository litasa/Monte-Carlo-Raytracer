#pragma once
#include "glm\glm.hpp"
class BRDF {
public:
	virtual ~BRDF() {}
	virtual glm::vec3 get(const glm::vec3 &surface_normal, const glm::vec3 &in, const glm::vec3 &out) = 0;
protected:
	BRDF() {}
	float _ks;
	float _kd;
};