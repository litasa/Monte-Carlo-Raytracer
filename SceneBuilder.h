#pragma once
#include "Scene.h"
#include "TempLightSource.h" //TODO: Change type to non-temporary
#include "TempPrimitive.h" //TODO: Change type to non-temporary
/// This is just an incapsulation of the creation of a scene object.
class SceneBuilder {
public:
	static void build_cornell_box(Scene &scene) {
		//Add light sources
		scene.add_light_source(TempLightSource(/*...*/)); //Area light source
		scene.add_light_source(TempLightSource(/*...*/)); //Area light source

		//Add surfaces
		scene.add_primitive(TempPrimitive(/*...*/)); //Implicit surface
		scene.add_primitive(TempPrimitive(/*...*/)); //Implicit surface
		scene.add_primitive(TempPrimitive(/*...*/)); //Implicit surface
		
		//Add walls
		scene.add_primitive(TempPrimitive(/*...*/)); //Ceiling plane
		scene.add_primitive(TempPrimitive(/*...*/)); //Floor plane
		scene.add_primitive(TempPrimitive(/*...*/)); //Left plane
		scene.add_primitive(TempPrimitive(/*...*/)); //Right plane
		scene.add_primitive(TempPrimitive(/*...*/)); //Back plane
	}
};