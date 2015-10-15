#pragma once
#include "Primitive.h"
#include <vector>
#include "glm\glm.hpp"
#include <iostream>
class Plane : public Primitive
{
public:
	Plane() = default;
	Plane(glm::vec3 position, std::shared_ptr<Material> material, glm::vec3 normal,
		float size_x = 15.01f, float size_y = 15.01f, float size_z = 15.01f)
		: Primitive(position, material), _normal(normal) , _size_x(size_x), _size_y(size_y), _size_z(size_z)
	{
		_d = -normal.x*position.x - normal.y*position.y - normal.z*position.z;
		points.push_back(position);
		
		if (normal == glm::vec3(0,1,0) || normal == glm::vec3(0,-1,0))
		{
			points.push_back(glm::vec3(position.x + size_x, position.y, position.z + size_z));
			points.push_back(glm::vec3(position.x - size_x, position.y, position.z + size_z));
			points.push_back(glm::vec3(position.x + size_x, position.y, position.z - size_z));
			points.push_back(glm::vec3(position.x - size_x, position.y, position.z - size_z));
			_area = size_x*size_z;
		}
		else if (normal == glm::vec3(1,0,0) || normal == glm::vec3(-1, 0, 0))
		{
			points.push_back(glm::vec3(position.x, position.y + size_y, position.z + size_z));
			points.push_back(glm::vec3(position.x, position.y - size_y, position.z + size_z));
			points.push_back(glm::vec3(position.x, position.y + size_y, position.z - size_z));
			points.push_back(glm::vec3(position.x, position.y - size_y, position.z - size_z));
			_area = size_y*size_z;
		}
		else if (normal == glm::vec3(0, 0, 1) || normal == glm::vec3(0, 0, -1))
		{
			points.push_back(glm::vec3(position.x + size_x, position.y + size_y, position.z));
			points.push_back(glm::vec3(position.x - size_x, position.y + size_y, position.z));
			points.push_back(glm::vec3(position.x + size_x, position.y - size_y, position.z));
			points.push_back(glm::vec3(position.x - size_x, position.y - size_y, position.z));
			_area = size_x*size_y;
		}
		else
		{
			_area = 0;
		}
	};
	
	glm::vec3 GetOffsetOnPlane(float x, float y)
	{
		if (_normal == glm::vec3(0,1,0) || _normal == glm::vec3(0,-1,0))
		{
			return glm::vec3(_position.x + x, _position.y, _position.z + y);
		}
		else if (_normal == glm::vec3(1,0,0) || _normal == glm::vec3(-1, 0, 0))
		{
			return glm::vec3(_position.x, _position.y + x, _position.z + y);
		}
		else if (_normal == glm::vec3(0, 0, 1) || _normal == glm::vec3(0, 0, -1))
		{
			return glm::vec3(_position.x + x, _position.y + y, _position.z);
		}
	};

	glm::vec3 intersection(const Ray &ray) override;
	glm::vec3 get_normal_at(const glm::vec3 &hit_point) override;
	PrimitiveType get_type() override { return PrimitiveType::Plane; }


	std::vector<glm::vec3> points;
	float _area;
private:
	glm::vec3 _normal;
	float _size_x;
	float _size_y;
	float _size_z;

	float _d;
};
