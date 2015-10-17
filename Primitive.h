#pragma once
#include <memory>
#include <vector>
#include "Ray.h"
#include "Material.h"
#include "BoundingBox.h"
class Primitive
{
public:
	virtual ~Primitive() {}
	Primitive(glm::vec3 position, std::shared_ptr<Material> material);

	enum PrimitiveType {
		Sphere,
		Plane,
		None,
	};

	virtual glm::vec3 intersection(const Ray &ray) = 0;
	virtual glm::vec3 get_normal_at(const glm::vec3 &position) = 0;
	virtual float area() = 0;
	virtual float uniform_pdf() = 0;
	virtual glm::vec3 uniform_random_sample() = 0;
	virtual void uniform_random_sample(int nr_samples, std::vector<glm::vec3> &samples) = 0;
	virtual PrimitiveType get_type() = 0;
	virtual const BoundingBox &get_bounds() const { return _box; }
	static const glm::vec3 _no_intersection;
	glm::vec3 _position;
	std::shared_ptr<Material> _material;

protected:
	Primitive() = default;
	BoundingBox _box;
};