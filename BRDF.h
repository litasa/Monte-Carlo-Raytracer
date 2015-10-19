#pragma once
#include "glm\glm.hpp"
#ifndef DEFAULT_ABSORPTION_CONSTANT
#define DEFAULT_ABSORPTION_CONSTANT 0.25
#endif
///The BRDF determines the probability that light is sent in some direction with respect to a surface normal.
///It is an abstract base class.
class BRDF {
public:
	//There are some different types of BRDFs, there are specular and diffuse surfaces. There's also a dummy one in our case for light sources.
	enum class BRDFType { DIFFUSE, DUMMY };
	virtual ~BRDF() {}
	//Get the probability for wavelengths being sent in the out direction given the surface information and the incoming light ray.
	virtual glm::vec3 get(const glm::vec3 &surface_normal, const glm::vec3 &in, const glm::vec3 &out) = 0;
	//Get the type of BRDF given by BRDFType
	virtual BRDFType get_type() = 0;
	//The absorption determines how much of the light is absorbed at the surface
	float get_absorption() const { return _absorption; }
	void set_absorption(float value) { _absorption = value; }
protected:
	BRDF() : _absorption(DEFAULT_ABSORPTION_CONSTANT) {}
	//Coefficients
	float _ks, _kd, _absorption;
};