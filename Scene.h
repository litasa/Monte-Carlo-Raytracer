#pragma once
#include <vector>
#include "TempLightSource.h" //TODO: Change type to non-temporary
#include "TempPrimitive.h" //TODO: Change type to non-temporary
//Scene is a lightweight class that has collections of scene objects
class Scene {
public:
	Scene() = default;
	void add_primitive(TempPrimitive primitive) { _primitives.push_back(primitive); } //TODO: Change type to non-temporary
	void add_light_source(TempLightSource light_source) { _light_sources.push_back(light_source); } //TODO: Change type to non-temporary
	const std::vector<TempPrimitive> &get_primitives() const { return _primitives; } //TODO: Change type to non-temporary
	const std::vector<TempLightSource> &get_light_sources() const { return _light_sources; } //TODO: Change type to non-temporary
private:
	std::vector<TempPrimitive> _primitives; //TODO: Change type to non-temporary
	std::vector<TempLightSource> _light_sources; //TODO: Change type to non-temporary
};