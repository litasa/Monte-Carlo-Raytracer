#pragma once
#include "BoundingBox.h"
struct BVHPrimitiveInfo {
	BVHPrimitiveInfo(int primitive_number, const BoundingBox &box) : _primitive_number(primitive_number), _box(box) {
		_centroid = 0.5f * box._min_point + 0.5f * box._max_point;
	}

	int _primitive_number;
	glm::vec3 _centroid;
	BoundingBox _box;
};
