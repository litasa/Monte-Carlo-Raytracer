#pragma once
#include "Primitive.h"
#include <vector>
#include "glm\glm.hpp"
#include <iostream>
#ifndef DEFAULT_PLANE_SIZE
#define DEFAULT_PLANE_SIZE 15.01f
#endif
class Plane : public Primitive
{
public:
	Plane() = default;
	Plane(glm::vec3 position, std::shared_ptr<Material> material, glm::vec3 normal,
		float size_x = DEFAULT_PLANE_SIZE, float size_y = DEFAULT_PLANE_SIZE, float size_z = DEFAULT_PLANE_SIZE);

	glm::vec3 get_offset_on_plane(float x, float y);
	glm::vec2 get_sizes();
	float area() override;
	float uniform_pdf() override;
	glm::vec3 uniform_random_sample() override;
	void uniform_random_sample(int nr_samples, std::vector<glm::vec3>& samples) override;
	glm::vec3 intersection(const Ray &ray) override;
	glm::vec3 get_normal_at(const glm::vec3 &hit_point) override;
	PrimitiveType get_type() override { return PrimitiveType::Plane; }
	const std::vector<glm::vec3> &get_points() const { return _points; }
private:
	glm::vec3 _normal;
	float _size_x;
	float _size_y;
	float _size_z;
	float _d;
	std::vector<glm::vec3> _points;
	glm::vec2 _half_sizes;
	float _area;
	float _inverse_area;
	void compute_area();
};
