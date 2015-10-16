#include "Plane.h"
#include "glm\glm.hpp"
#include "glm\gtc\random.hpp"
#include <iostream>

Plane::Plane(glm::vec3 position, std::shared_ptr<Material> material, glm::vec3 normal, float size_x, float size_y, float size_z)
	: Primitive(position, material), _normal(normal), _size_x(size_x), _size_y(size_y), _size_z(size_z), _d(-glm::dot(normal, position))
{
	compute_area();
	//This is used often
	_half_sizes = get_sizes() * 0.5f;
}

glm::vec3 Plane::intersection(const Ray &ray)
{
	float intersection(glm::dot(_normal, ray._origin) + _d);
	float angle(glm::dot(ray._direction, _normal));
	if ((intersection > 0 && angle > 0) || (intersection < 0 && angle < 0))
	{
		return _no_intersection;
	}

	float t = -intersection / angle;
	glm::vec3 hit_point = ray._origin + t * ray._direction;
	//All these conditions need to be fullfilled, thus we discard if one of the conditions are false
	if (glm::abs(hit_point.x - _position.x) <= _size_x && glm::abs(hit_point.y - _position.y) <= _size_y && glm::abs(hit_point.z - _position.z) <= _size_z) {
		return hit_point;
	}

	return _no_intersection;
}

void Plane::compute_area() {
	_area = 0.0f;
	//Save mid-point
	_points.push_back(_position);
	//Works only for axis aligned bounded planes.
	if (glm::abs(_normal.y))
	{
		_points.push_back(glm::vec3(_position.x + _size_x, _position.y, _position.z + _size_z));
		_points.push_back(glm::vec3(_position.x - _size_x, _position.y, _position.z + _size_z));
		_points.push_back(glm::vec3(_position.x + _size_x, _position.y, _position.z - _size_z));
		_points.push_back(glm::vec3(_position.x - _size_x, _position.y, _position.z - _size_z));
		_area = _size_x * _size_z;
	}
	else if (glm::abs(_normal.x))
	{
		_points.push_back(glm::vec3(_position.x, _position.y + _size_y, _position.z + _size_z));
		_points.push_back(glm::vec3(_position.x, _position.y - _size_y, _position.z + _size_z));
		_points.push_back(glm::vec3(_position.x, _position.y + _size_y, _position.z - _size_z));
		_points.push_back(glm::vec3(_position.x, _position.y - _size_y, _position.z - _size_z));
		_area = _size_y * _size_z;
	}
	else if (glm::abs(_normal.z))
	{
		_points.push_back(glm::vec3(_position.x + _size_x, _position.y + _size_y, _position.z));
		_points.push_back(glm::vec3(_position.x - _size_x, _position.y + _size_y, _position.z));
		_points.push_back(glm::vec3(_position.x + _size_x, _position.y - _size_y, _position.z));
		_points.push_back(glm::vec3(_position.x - _size_x, _position.y - _size_y, _position.z));
		_area = _size_x * _size_y;
	}
	//Save the "inverse" of the area for uniform sampling
	_inverse_area = 1.0f / _area;
}

float Plane::area() {
	return _area;
}

float Plane::uniform_pdf() {
	return _inverse_area;
}

glm::vec3 Plane::uniform_random_sample() {
	return get_offset_on_plane(glm::linearRand(-_half_sizes.s, _half_sizes.s), glm::linearRand(-_half_sizes.t, _half_sizes.t));
}

void Plane::uniform_random_sample(int nr_samples, std::vector<glm::vec3>& samples) {
	for (int i = 0; i < nr_samples; ++i) {
		samples.push_back(get_offset_on_plane(glm::linearRand(-_half_sizes.s, _half_sizes.s), glm::linearRand(-_half_sizes.t, _half_sizes.t)));
	}
}

glm::vec2 Plane::get_sizes() {
	glm::vec2 sizes(0);
	if (glm::abs(_normal.y)) {
		sizes = glm::vec2(_size_x, _size_z);
	}
	else if (glm::abs(_normal.x)) {
		sizes = glm::vec2(_size_y, _size_z);
	}
	else if (glm::abs(_normal.z)) {
		sizes = glm::vec2(_size_x, _size_y);
	}
	return sizes;
}

glm::vec3 Plane::get_offset_on_plane(float x, float y) {
	glm::vec3 point_on_plane(0);
	if (glm::abs(_normal.y)) {
		point_on_plane = glm::vec3(_position.x + x, _position.y, _position.z + y);
	}
	else if (glm::abs(_normal.x)) {
		point_on_plane = glm::vec3(_position.x, _position.y + x, _position.z + y);
	}
	else if (glm::abs(_normal.z)) {
		point_on_plane = glm::vec3(_position.x + x, _position.y + y, _position.z);
	}
	return point_on_plane;
}

glm::vec3 Plane::get_normal_at(const glm::vec3 &hit_point) {
	return _normal;
}