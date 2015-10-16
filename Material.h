#pragma once
#include <memory>
#include <iostream>
#include "glm\glm.hpp"
#include "BRDF.h"
class Material
{
public:
	Material(const glm::vec3 &color, const glm::vec3 &emitted, const std::shared_ptr<BRDF> &brdf)
		: _color(color), _emitted(emitted), _brdf(brdf)
	{
		if (_brdf == nullptr) {
			std::cout << "\nWarning: BRDF for a primitive is nullptr. Check scene specifications." << std::endl;
		}
	}
	~Material() {}
	const glm::vec3 &get_color() const { return _color; }
	const glm::vec3 &get_emitted() const { return _emitted; }
	const std::shared_ptr<BRDF> &get_brdf() const { return _brdf; }
	glm::vec3 get_brdf_color_mult(const glm::vec3 &surface_normal, const glm::vec3 &in, const glm::vec3 &out) { return _color * _brdf->get(surface_normal, in, out); }
private:
	glm::vec3 _color;
	glm::vec3 _emitted;
	std::shared_ptr<BRDF> _brdf;
};

