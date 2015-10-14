#pragma once
#include <memory>
#include "Scene.h"
#include "Primitive.h"
#include "Plane.h"
#include "Sphere.h"
#include "LightMaterial.h"
#include "DiffuseMaterial.h"
/// This is just an incapsulation of the creation of a scene object.
class SceneBuilder {
public:
	static void build_cornell_box(Scene &scene) {
		//Add light sources
		std::shared_ptr<Plane> area_light = std::make_shared<Plane>(glm::vec3(0.0f, 14.99f, 0), std::make_shared<LightMaterial>(glm::vec3(1.0, 1.0, 1.0)), glm::vec3(0, -1, 0), 5.0f, 5.0f, 5.0f);
		scene.add_primitive(area_light); //Area light source
		scene.add_light_source(area_light); //Area light source

		//Add surfaces
		scene.add_primitive(std::make_shared<Sphere>(glm::vec3(0, 0, 0), std::make_shared<DiffuseMaterial>(glm::vec3(1.0, 0.0, 1.0)), 5.0f)); //Implicit surface
		//scene.add_primitive(std::make_shared<Sphere>(glm::vec3(0, 10, 0), nullptr, 1.0f)); //Implicit surface
		//scene.add_primitive(std::make_shared<Sphere>(glm::vec3(0, 10, 0), nullptr, 1.0f)); //Implicit surface

		//Add walls
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0, 15, 0), std::make_shared<DiffuseMaterial>(glm::vec3(1.0, 1.0, 0.0)), glm::vec3(0, -1, 0))); //Ceiling plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0, -15, 0), std::make_shared<DiffuseMaterial>(glm::vec3(0.0, 1.0, 0.0)), glm::vec3(0, 1, 0))); //Floor plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(-15, 0, 0), std::make_shared<DiffuseMaterial>(glm::vec3(1.0, 0.0, 0.0)), glm::vec3(1, 0, 0))); //Left plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(15, 0, 0), std::make_shared<DiffuseMaterial>(glm::vec3(0.0, 1.0, 1.0)), glm::vec3(-1, 0, 0))); //Right plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0, 0, 15), std::make_shared<DiffuseMaterial>(glm::vec3(0.0, 0.0, 1.0)), glm::vec3(0, 0, -1))); //Back plane
	}
};