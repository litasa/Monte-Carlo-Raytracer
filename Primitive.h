#pragma once
#include <memory>
#include "Ray.h"
#include "Material.h"
class Primitive
{
public:
	virtual ~Primitive() {}
	Primitive(glm::vec3 position, std::shared_ptr<Material> material) : _position(position), _material(material) {};
	
	enum PrimitiveType {
		Sphere,
		Plane,
		None,
	};

	virtual glm::vec3 intersection(const Ray &ray) = 0;
	virtual glm::vec3 get_normal_at(const glm::vec3 &position) = 0;
	virtual PrimitiveType get_type() = 0;

	static const glm::vec3 _no_intersection;

	glm::vec3 _position;
	std::shared_ptr<Material> _material;

protected:
	Primitive() = default;
};