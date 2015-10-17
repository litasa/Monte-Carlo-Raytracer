#pragma once
#include "glm\glm.hpp"
class BRDF {
public:
	enum class BRDFType {
		DIFFUSE,
		DUMMY,
	};

	virtual ~BRDF() {}
	virtual glm::vec3 get(const glm::vec3 &surface_normal, const glm::vec3 &in, const glm::vec3 &out) = 0;
	virtual BRDFType get_type() = 0;
	float get_absorption() const { return _absorption; }
	void set_absorption(float value) { _absorption = value; }
	
protected:
	BRDF() : _absorption(0.25) {}
	float _ks;
	float _kd;
	float _absorption;
};