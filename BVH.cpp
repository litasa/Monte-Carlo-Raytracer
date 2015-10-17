#include "BVH.h"
#include <array>

void BVH::initialize(const std::vector<std::shared_ptr<Primitive>> &primitives, int max_node_primitives) {
	if (primitives.empty()) {
		std::cout << "\nWarning: No primitives added to the bounding volume hierarchy." << std::endl;
		return;
	}

	_primitives = primitives;
	_max_node_primitives = max_node_primitives;

	//Collect data to build tree
	std::vector<BVHPrimitiveInfo> build_data;
	for (int i = 0; i < primitives.size(); ++i) {
		const BoundingBox &box = primitives.at(i)->get_bounds();
		build_data.push_back(BVHPrimitiveInfo(i, box));
	}

	//Recursively build tree
	std::vector<std::shared_ptr<Primitive>> ordered_primitives;
	_total_nodes = 0;
	_nodes = recursive_build(build_data, 0, primitives.size(), _total_nodes, ordered_primitives);
}

bool BVH::intersect(const Ray &ray) {
	if (_nodes == nullptr) {
		return false;
	}

	bool hit = false;
	glm::vec3 point = ray._origin;
	glm::vec3 inv_ray = ray._inv_direction;
	std::array<int, 3> neg_dir = { inv_ray.x < 0, inv_ray.y < 0, inv_ray.z < 0};

	int node_nr = 0;

	return hit;
}

std::shared_ptr<BVHBuildNode> BVH::recursive_build(std::vector<BVHPrimitiveInfo> &build_data, int start, int end, int &total_nodes, std::vector<std::shared_ptr<Primitive>> &ordered_primitives) {
	std::shared_ptr<BVHBuildNode> node = std::make_shared<BVHBuildNode>();
	BoundingBox box(glm::vec3(0));
	for (int i = start; i < end; ++i) {
		box = box.union_operator(box, build_data.at(i)._box);
	}

	int primitives_number = end - start;
	if (primitives_number == 1) {
		int first_offset = ordered_primitives.size();
		for (int i = start; i < end; ++i) {
			int primitive_number = build_data.at(i)._primitive_number;
			ordered_primitives.push_back(_primitives.at(i));
		}
		node->init_leaf(first_offset, primitives_number, box);
	}
	else {
		BoundingBox centroid_box(glm::vec3(0));
		for (int i = start; i < end; ++i) {
			centroid_box = centroid_box.union_operator(centroid_box, build_data.at(i)._centroid);
		}
		int dimension = centroid_box.maximum_extent();
		int mid = (start + end) / 2;
		if (centroid_box._max_point[dimension] == centroid_box._min_point[dimension]) {
			//Extract to method
			int first_offset = ordered_primitives.size();
			for (int i = start; i < end; ++i) {
				int primitive_number = build_data.at(i)._primitive_number;
				ordered_primitives.push_back(_primitives.at(i));
			}
			node->init_leaf(first_offset, primitives_number, box);
			return node;
		}

		//Partition with split midpoint for now
		float midpoint = 0.5f * (centroid_box._min_point[dimension] + centroid_box._max_point[dimension]);
		BVHPrimitiveInfo *mid_pointer = std::partition(&build_data.at(start), &build_data.at(end), CompareToMid(dimension, midpoint));
		mid = mid_pointer - &build_data[0];
		node->init_interior(dimension, recursive_build(build_data, start, mid, total_nodes, ordered_primitives),
			recursive_build(build_data, mid, end, total_nodes, ordered_primitives));
	}

	return node;
}