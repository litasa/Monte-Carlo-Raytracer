#pragma once
#include <vector>
#include <memory>
#include "Primitive.h"
//Scene is a lightweight class that has collections of scene objects
class Scene {
public:
	Scene() = default;
	void add_primitive(std::shared_ptr<Primitive> primitive) { _primitives.push_back(primitive); }
	void add_light_source(std::shared_ptr<Primitive> light_source) { _light_sources.push_back(light_source); }
	const std::vector<std::shared_ptr<Primitive>> &get_primitives() const { return _primitives; }
	const std::vector<std::shared_ptr<Primitive>> &get_light_sources() const { return _light_sources; }
private:
	std::vector<std::shared_ptr<Primitive>> _primitives;
	std::vector<std::shared_ptr<Primitive>> _light_sources;
};