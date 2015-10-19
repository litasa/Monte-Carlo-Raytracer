#pragma once
#include <vector>
#include <memory>
#include "Primitive.h"
///Scene is a lightweight class that has collections of scene objects.
///A good extension to this class would be to include some sort of spatial partitioning that returns the primitives that a ray might intersect
class Scene {
public:
	Scene() = default;
	//Two separate vectors for light sources and other primitives, this is due to performance reasons. For shadow ray casting we only need to check for lights
	void add_primitive(std::shared_ptr<Primitive> primitive) { _primitives.push_back(primitive); }
	void add_light_source(std::shared_ptr<Primitive> light_source) { _light_sources.push_back(light_source); }
	//Getters for these vectors, keeping them non-mutable
	const std::vector<std::shared_ptr<Primitive>> &get_primitives() const { return _primitives; }
	const std::vector<std::shared_ptr<Primitive>> &get_light_sources() const { return _light_sources; }
private:
	std::vector<std::shared_ptr<Primitive>> _primitives;
	std::vector<std::shared_ptr<Primitive>> _light_sources;
};