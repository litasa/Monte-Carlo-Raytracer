#pragma once
#include <vector>
#include "Primitive.h"
//Scene is a lightweight class that has collections of scene objects
class Scene {
public:
	Scene() = default;
	void add_primitive(Primitive primitive) { _primitives.push_back(primitive); } //TODO: Change type to non-temporary
	void add_light_source(Primitive light_source) { _light_sources.push_back(light_source); } //TODO: Change type to non-temporary
	const std::vector<Primitive> &get_primitives() const { return _primitives; } //TODO: Change type to non-temporary
	const std::vector<Primitive> &get_light_sources() const { return _light_sources; } //TODO: Change type to non-temporary
private:
	std::vector<Primitive> _primitives; //TODO: Change type to non-temporary
	std::vector<Primitive> _light_sources; //TODO: Change type to non-temporary
};