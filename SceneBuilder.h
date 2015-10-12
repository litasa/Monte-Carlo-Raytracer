#pragma once
#include "Scene.h"
#include "Primitive.h" //TODO: Change type to non-temporary
/// This is just an incapsulation of the creation of a scene object.
class SceneBuilder {
public:
	static void build_cornell_box(Scene &scene) {
		//Add light sources
		scene.add_light_source(Primitive(/*...*/)); //Area light source
		scene.add_light_source(Primitive(/*...*/)); //Area light source

		//Add surfaces
		scene.add_primitive(Primitive(/*...*/)); //Implicit surface
		scene.add_primitive(Primitive(/*...*/)); //Implicit surface
		scene.add_primitive(Primitive(/*...*/)); //Implicit surface
		
		//Add walls
		scene.add_primitive(Primitive(/*...*/)); //Ceiling plane
		scene.add_primitive(Primitive(/*...*/)); //Floor plane
		scene.add_primitive(Primitive(/*...*/)); //Left plane
		scene.add_primitive(Primitive(/*...*/)); //Right plane
		scene.add_primitive(Primitive(/*...*/)); //Back plane
	}
};