#pragma once
#include "Primitive.h"
class Plane : public Primitive
{
public:
	Plane() = default;
	Plane(glm::vec3 pos, std::shared_ptr<Material> mat, glm::vec3 norm) : Primitive(pos, mat), _normal(norm) 
	{
		_d = -norm.x*pos.x - norm.y*pos.y - norm.z*pos.z;
	};

	glm::vec3 intersection(std::shared_ptr<Ray> ray) override;
	glm::vec3 get_normal_at(const glm::vec3 &hit_point) override;

private:
	float _d;
	glm::vec3 _normal;
};
