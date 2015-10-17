#pragma once
#include "Primitive.h"
class Sphere : public Primitive
{
public:
	Sphere() = default;
	Sphere(glm::vec3 position, std::shared_ptr<Material> material, float radius) : Primitive(position, material), _radius(radius) {
		_box = BoundingBox(position + radius);
	};

	glm::vec3 intersection(const Ray &ray) override;
	glm::vec3 get_normal_at(const glm::vec3 &hit_point) override;
	PrimitiveType get_type() override { return PrimitiveType::Sphere; }

private:
	float _radius;

	// Inherited via Primitive
	virtual float area() override;
	virtual float uniform_pdf() override;
	virtual glm::vec3 uniform_random_sample() override;
	virtual void uniform_random_sample(int nr_samples, std::vector<glm::vec3>& samples) override;
};

