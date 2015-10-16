#include "Primitive.h"
#include "glm\glm.hpp"
const glm::vec3 Primitive::_no_intersection = glm::vec3(-100);
Primitive::Primitive(glm::vec3 position, std::shared_ptr<Material> material)
	: _position(position), _material(material)
{
}
