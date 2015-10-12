#pragma once
#include <memory>
#include "Scene.h"
#include "Primitive.h"
#include "Plane.h"
#include "Sphere.h"
/// This is just an incapsulation of the creation of a scene object.
class SceneBuilder {
public:
	static void build_cornell_box(Scene &scene) {
		//Add light sources
		scene.add_light_source(std::make_shared<Plane>()); //Area light source
		scene.add_light_source(std::make_shared<Plane>()); //Area light source

		//Add surfaces
		scene.add_primitive(std::make_shared<Sphere>()); //Implicit surface
		scene.add_primitive(std::make_shared<Sphere>()); //Implicit surface
		scene.add_primitive(std::make_shared<Sphere>()); //Implicit surface
		
		//Add walls
		scene.add_primitive(std::make_shared<Plane>()); //Ceiling plane
		scene.add_primitive(std::make_shared<Plane>()); //Floor plane
		scene.add_primitive(std::make_shared<Plane>()); //Left plane
		scene.add_primitive(std::make_shared<Plane>()); //Right plane
		scene.add_primitive(std::make_shared<Plane>()); //Back plane
	}
};