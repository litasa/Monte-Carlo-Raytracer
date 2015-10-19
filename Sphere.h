#pragma once
#include "Primitive.h"
#include "glm\gtc\constants.hpp"
///This is a derived class of the abstract base class Primitive.
///A Sphere is defined by its center and radius along with its surface material.
class Sphere : public Primitive {
public:
	Sphere(glm::vec3 position, std::shared_ptr<Material> material, float radius) : Primitive(position, material), _radius(radius) {
		//These are used frequently for intersection checks
		_radius_squared = _radius * _radius;
		_area = 2.0f * glm::two_pi<float>() * _radius_squared;
		_inverse_area = 1.0f / _area;
	};
	glm::vec3 intersection(const Ray &ray) override;
	glm::vec3 get_normal_at(const glm::vec3 &hit_point) override;
private:
	float _radius, _radius_squared, _area, _inverse_area;
	//Inherited from Primitive
	virtual float area() override;
	virtual float uniform_pdf() override;
	virtual glm::vec3 uniform_random_sample() override;
	virtual void uniform_random_sample(int nr_samples, std::vector<glm::vec3>& samples) override;
};

