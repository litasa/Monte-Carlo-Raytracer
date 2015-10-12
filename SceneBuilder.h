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
		//scene.add_light_source(std::make_shared<Plane>(); //Area light source
		//scene.add_light_source(std::make_shared<Plane>()); //Area light source

		//Add surfaces
		scene.add_primitive(std::make_shared<Sphere>(glm::vec3(5, 5, 5), nullptr, 5.0f)); //Implicit surface
		//scene.add_primitive(std::make_shared<Sphere>(glm::vec3(0, 10, 0), nullptr, 1.0f)); //Implicit surface
		//scene.add_primitive(std::make_shared<Sphere>(glm::vec3(0, 10, 0), nullptr, 1.0f)); //Implicit surface

		//Add walls
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0, 10, 0), nullptr, glm::vec3(0, -1, 0))); //Ceiling plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0, 0, 0), nullptr, glm::vec3(0, 1, 0))); //Floor plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0, 0, 10), nullptr, glm::vec3(1, 0, 0))); //Left plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(10, 0, 10), nullptr, glm::vec3(-1, 0, 0))); //Right plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0, 0, 10), nullptr, glm::vec3(0, 0, -1))); //Back plane
	}
};