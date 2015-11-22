#pragma once
#include "Primitive.h"
#include <vector>
#include "glm\glm.hpp"
#ifndef DEFAULT_PLANE_SIZE
#define DEFAULT_PLANE_SIZE 15.01f
#endif
///A plane is a derived class of the abstract base class Primtive. It takes a position and a normal along with the surface material.
class Plane : public Primitive
{
public:
	Plane() = default;
	Plane(glm::vec3 position, std::shared_ptr<Material> material, glm::vec3 normal,
		float size_x = DEFAULT_PLANE_SIZE, float size_y = DEFAULT_PLANE_SIZE, float size_z = DEFAULT_PLANE_SIZE);
	//Gets a position inside the plane for bounded planes
	glm::vec3 get_offset_on_plane(float x, float y);
	//Get the sizes of the planes, axis aligned so only 2 dimensions
	glm::vec2 get_sizes();
	//Get the center and corner points for this plane
	const std::vector<glm::vec3> &get_points() const { return _points; }
	//Inherited from Primitive
	float area() override;
	float uniform_pdf() override;
	glm::vec3 uniform_random_sample() override;
	void uniform_random_sample(int nr_samples, std::vector<glm::vec3>& samples) override;
	glm::vec3 intersection(const Ray &ray) override;
	glm::vec3 get_normal_at(const glm::vec3 &hit_point) override;
private:
	glm::vec3 _normal, _t_hat, _s_hat;
	float _size_x, _size_y, _size_z, _d, _area, _inverse_area, _epsilon;
	std::vector<glm::vec3> _points;
	glm::vec2 _half_sizes;
	//The area needs some consideration because the plane is axis aligned
	void compute_area();
};
