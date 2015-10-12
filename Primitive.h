#pragma once
#include <memory>
#include "Ray.h"
#include "Material.h"
class Primitive
{
public:
	Primitive() = default;
	Primitive(glm::vec3 position, std::shared_ptr<Material> material) : _position(position), _material(material) {};

	virtual glm::vec3 intersection(std::shared_ptr<Ray> ray) = 0;
	virtual glm::vec3 get_normal_at(const glm::vec3 &position) = 0;

	glm::vec3 _position;
	std::shared_ptr<Material> _material;
};