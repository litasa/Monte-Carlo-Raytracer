#pragma once
#include "Primitive.h"
class Plane : public Primitive
{
public:
	Plane() = default;
	Plane(glm::vec3 position, std::shared_ptr<Material> material, glm::vec3 normal,
		float size_x = 50.0f, float size_y = 50.0f, float size_z = 50.0f)
		: Primitive(position, material), _normal(normal) , _size_x(size_x), _size_y(size_y), _size_z(size_z)
	{
		_d = -normal.x*position.x - normal.y*position.y - normal.z*position.z;
	};
	Plane(glm::vec3 position, std::shared_ptr<Material> material, glm::vec3 normal,
		float size)
		: Primitive(position, material), _normal(normal), _size_x(size), _size_y(size), _size_z(size)
	{
		_d = -normal.x*position.x - normal.y*position.y - normal.z*position.z;
	};

	glm::vec3 intersection(const Ray &ray) override;
	glm::vec3 get_normal_at(const glm::vec3 &hit_point) override;
	PrimitiveType get_type() override { return PrimitiveType::Plane; }

private:
	glm::vec3 _normal;
	float _size_x;
	float _size_y;
	float _size_z;

	float _d;
};
