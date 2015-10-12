#pragma once
#include "Primitive.h"
class Sphere : public Primitive
{
public:
	Sphere() = default;
	Sphere(glm::vec3 position, std::shared_ptr<Material> material, float radius) : Primitive(position, material), _radius(radius) {};

	glm::vec3 intersection(const Ray &ray) override;
	glm::vec3 get_normal_at(const glm::vec3 &hit_point) override;
	PrimitiveType get_type() override { return PrimitiveType::Sphere; }

private:
	float _radius;
};

