#pragma once
#include "Primitive.h"
class Sphere : public Primitive
{
public:
	Sphere() = default;
	Sphere(glm::vec3 position, std::shared_ptr<Material> material, float radius) : Primitive(position, material), _radius(radius) {};

	glm::vec3 intersection(std::shared_ptr<Ray> ray) override;
	glm::vec3 get_normal_at(const glm::vec3 &hit_point) override;

private:
	float _radius;
};

