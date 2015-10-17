#pragma once
#include <memory>
#include "BoundingBox.h"
struct BVHBuildNode {
	BVHBuildNode() {}

	void init_leaf(int first_offset, int primitive_number, const BoundingBox &box) {
		_first_offset = first_offset;
		_primitive_number = primitive_number;
		_box = box;
	}

	void init_interior(int split_axis, const std::shared_ptr<BVHBuildNode> &child_one, const std::shared_ptr<BVHBuildNode> &child_two) {
		_child_one = child_one;
		_child_two = child_two;
		_box = _box.union_operator(child_one->_box, child_two->_box);
		_split_axis = split_axis;
		_primitive_number = 0;
	}

	BoundingBox _box;
	std::shared_ptr<BVHBuildNode> _child_one;
	std::shared_ptr<BVHBuildNode> _child_two;
	int _split_axis, _first_offset, _primitive_number;
};
