#pragma once
#include "Primitive.h"
class Plane : public Primitive
{
public:
	Plane() = default;
	Plane(glm::vec3 position, std::shared_ptr<Material> material, glm::vec3 normal) : Primitive(position, material), _normal(normal) 
	{
		_d = -normal.x*position.x - normal.y*position.y - normal.z*position.z;
	};

	glm::vec3 intersection(const Ray &ray) override;
	glm::vec3 get_normal_at(const glm::vec3 &hit_point) override;
	PrimitiveType get_type() override { return PrimitiveType::Plane; }

private:
	float _d;
	glm::vec3 _normal;
};
