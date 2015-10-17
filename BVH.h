#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "Primitive.h"
#include "BoundingBox.h"
#include "BVHBuildNode.h"
#include "BVHPrimitiveData.h"

class BVH {
public:

	struct CompareToMid {
		CompareToMid(int dimension, float midpoint) : _dimension(dimension), _midpoint(midpoint) {}
		int _dimension;
		float _midpoint;
		bool operator() (const BVHPrimitiveInfo &info) const {
			return info._centroid[_dimension] < _midpoint;
		}
	};

	BVH() = default;
	void initialize(const std::vector<std::shared_ptr<Primitive>> &primitives, int max_node_primitives);
	bool intersect(const Ray &ray);

private:
	std::shared_ptr<BVHBuildNode> recursive_build(std::vector<BVHPrimitiveInfo> &build_data, int start, int end, int &total_nodes, std::vector<std::shared_ptr<Primitive>> &ordered_primitives);
	int _max_node_primitives;
	std::vector<std::shared_ptr<Primitive>> _primitives;
	std::shared_ptr<BVHBuildNode> _nodes;
	int _total_nodes;
};