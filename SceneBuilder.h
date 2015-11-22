#pragma once
#include <memory>
#include "Scene.h"
#include "Primitive.h"
#include "Plane.h"
#include "Sphere.h"
#include "Material.h"
#include "DummyBRDF.h"
#include "DiffuseBRDF.h"
#include "OrenNayarBRDF.h"
/// This is just an incapsulation of the creation of a scene object.
class SceneBuilder {
public:
	//Create a virtual version of the Cornell box 
	static void build_cornell_box(Scene &scene) {
		//Create the BRDFs
		std::shared_ptr<DummyBRDF> dummy_brdf = std::make_shared<DummyBRDF>();
		std::shared_ptr<DiffuseBRDF> diffuse_brdf = std::make_shared<DiffuseBRDF>();
		std::shared_ptr<DiffuseBRDF> second_diffuse_brdf = std::make_shared<DiffuseBRDF>();
		second_diffuse_brdf->set_absorption(0.0f);
		std::shared_ptr<OrenNayarBRDF> oren_diffuse_brdf = std::make_shared<OrenNayarBRDF>();
		//Add light sources to both vectors, easier to compare if light was intersected
		std::shared_ptr<Plane> area_light1 = std::make_shared<Plane>(glm::vec3(5.0f, 14.99f, 5.0f), std::make_shared<Material>(glm::vec3(1.0f), glm::vec3(1.0f), dummy_brdf), glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		std::shared_ptr<Plane> area_light2 = std::make_shared<Plane>(glm::vec3(-5.0f, 14.99f, 5.0f), std::make_shared<Material>(glm::vec3(1.0f), glm::vec3(1.0f), dummy_brdf), glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		std::shared_ptr<Plane> area_light3 = std::make_shared<Plane>(glm::vec3(5.0f, 14.99f, -5.0f), std::make_shared<Material>(glm::vec3(1.0f), glm::vec3(1.0f), dummy_brdf), glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		std::shared_ptr<Plane> area_light4 = std::make_shared<Plane>(glm::vec3(-5.0f, 14.99f, -5.0f), std::make_shared<Material>(glm::vec3(1.0f), glm::vec3(1.0f), dummy_brdf), glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		scene.add_primitive(area_light1); scene.add_light_source(area_light1);
		scene.add_primitive(area_light2); scene.add_light_source(area_light2);
		scene.add_primitive(area_light3); scene.add_light_source(area_light3);
		scene.add_primitive(area_light4); scene.add_light_source(area_light4);
		//Add surfaces
		scene.add_primitive(std::make_shared<Sphere>(glm::vec3(9.0f, -10.0f, -5.0f), std::make_shared<Material>(glm::vec3(0.5f), glm::vec3(0.0f), oren_diffuse_brdf), 5.0f)); //Implicit surface
		scene.add_primitive(std::make_shared<Sphere>(glm::vec3(-5.0f, -10.0f, 9.0f), std::make_shared<Material>(glm::vec3(0.5f), glm::vec3(0.0f), oren_diffuse_brdf), 5.0f)); //Implicit surface
		//Add walls
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0.0f, 15.0f, 0.0f), std::make_shared<Material>(glm::vec3(0.32f, 0.31f, 0.33f), glm::vec3(0.0f), second_diffuse_brdf), glm::vec3(0.0f, -1.0f, 0.0f))); //Ceiling plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0.0f, -15.0f, 0.0f), std::make_shared<Material>(glm::vec3(0.31f, 0.31f, 0.32f), glm::vec3(0.0f), diffuse_brdf), glm::vec3(0.0f, 1.0f, 0.0f))); //Floor plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(-15.0f, 0.0f, 0.0f), std::make_shared<Material>(glm::vec3(0.3f, 0.001f, 0.001f), glm::vec3(0.0f), diffuse_brdf), glm::vec3(1.0f, 0.0f, 0.0f))); //Left plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(15.0f, 0.0f, 0.0f), std::make_shared<Material>(glm::vec3(0.001f, 0.3f, 0.001f), glm::vec3(0.0f), diffuse_brdf), glm::vec3(-1.0f, 0.0f, 0.0f))); //Right plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0.0f, 0.0f, 15.0f), std::make_shared<Material>(glm::vec3(0.31f, 0.33f, 0.31f), glm::vec3(0.0f), diffuse_brdf), glm::vec3(0.0f, 0.0f, -1.0f))); //Back plane
	}
};