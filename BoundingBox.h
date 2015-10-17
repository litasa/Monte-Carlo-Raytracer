#pragma once
#include <limits>
#include "glm\glm.hpp"
#include "Ray.h"
class BoundingBox {
public:
	BoundingBox() {
		float inf = std::numeric_limits<float>().infinity();
		_min_point = glm::vec3(-inf, -inf, -inf);
		_max_point = glm::vec3(inf, inf, inf);
	}
	BoundingBox(const glm::vec3 &point) : _min_point(-point), _max_point(point) {}
	BoundingBox(const glm::vec3 &point_1, const glm::vec3 &point_2) {
		_min_point = glm::vec3(glm::min(point_1, point_2));
		_max_point = glm::vec3(glm::max(point_1, point_2));
	}

	BoundingBox union_operator(const BoundingBox &box, const glm::vec3 &point) {
		BoundingBox new_box;
		new_box._min_point.x = glm::min(box._min_point.x, point.x);
		new_box._min_point.y = glm::min(box._min_point.y, point.y);
		new_box._min_point.z = glm::min(box._min_point.z, point.z);
		new_box._max_point.x = glm::max(box._max_point.x, point.x);
		new_box._max_point.y = glm::max(box._max_point.y, point.y);
		new_box._max_point.z = glm::max(box._max_point.z, point.z);
		return new_box;
	}

	BoundingBox union_operator(const BoundingBox &box_1, const BoundingBox &box_2) {
		BoundingBox new_box;
		new_box._min_point.x = glm::min(box_1._min_point.x, box_2._min_point.x);
		new_box._min_point.y = glm::min(box_1._min_point.y, box_2._min_point.y);
		new_box._min_point.z = glm::min(box_1._min_point.z, box_2._min_point.z);
		new_box._max_point.x = glm::max(box_1._max_point.x, box_2._max_point.x);
		new_box._max_point.y = glm::max(box_1._max_point.y, box_2._max_point.y);
		new_box._max_point.z = glm::max(box_1._max_point.z, box_2._max_point.z);
		return new_box;
	}

	bool overlaps(const BoundingBox &box) {
		bool x = (_max_point.x >= box._min_point.x) && (_min_point.x <= box._max_point.x);
		bool y = (_max_point.y >= box._min_point.y) && (_min_point.y <= box._max_point.y);
		bool z = (_max_point.z >= box._min_point.z) && (_min_point.z <= box._max_point.z);
		return x && y && z;
	}

	bool inside(const glm::vec3 &point) {
		return (point.x <= _max_point.x && point.x >= _min_point.x) &&
			(point.y <= _max_point.y && point.y >= _min_point.y) &&
			(point.z <= _max_point.z && point.z >= _min_point.z);
	}

	bool intersect(const Ray &ray, float &hit_0, float &hit_1) {
		float t_0 = std::numeric_limits<float>().min();
		float t_1 = std::numeric_limits<float>().max();
		//Three component vectors
		for (int i = 0; i < 2; ++i) { 
			float inv_ray = ray._inv_direction[i];
			float t_near = (_min_point[i] - ray._origin[i]) * inv_ray;
			float t_far = (_max_point[i] - ray._origin[i]) * inv_ray;

			if (t_near > t_far) {
				float temp = t_near;
				t_far = t_near;
				t_near = t_far;
			}

			t_0 = t_near > t_0 ? t_near : t_0;
			t_1 = t_far < t_1 ? t_far : t_1;

			if (t_0 > t_1) {
				return false;
			}
		}

		if (hit_0) {
			hit_0 = t_0;
		}
		
		if (hit_1) {
			hit_1 = t_1;
		}
	}

	void expand(float amount) {
		_min_point -= glm::vec3(amount);
		_max_point += glm::vec3(amount);
	}

	float area() {
		glm::vec3 diagonal = _max_point - _min_point;
		return 2.0f * (diagonal.x * diagonal.y + diagonal.x * diagonal.z + diagonal.y * diagonal.z);
	}

	float volume() {
		glm::vec3 diagonal = _max_point - _min_point;
		return diagonal.x * diagonal.y * diagonal.z;
	}

	int maximum_extent() const {
		glm::vec3 diagonal = _max_point - _min_point;
		if (diagonal.x > diagonal.y && diagonal.x < diagonal.z) {
			return 0;
		}
		else if (diagonal.y > diagonal.z) {
			return 1;
		}
		else {
			return 2;
		}
	}

	glm::vec3 _min_point;
	glm::vec3 _max_point;
};
