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
#include "ReflectionBRDF.h"
#include "DiffuseMaterial.h"
#include "DummyMaterial.h"
//#include "TransparentBRDF.h"
/// This is just an incapsulation of the creation of a scene object.
class SceneBuilder {
public:
	//Create a virtual version of the Cornell box 
	static void build_cornell_box(Scene &scene) {
		//Create the BRDFs
		std::shared_ptr<DummyBRDF> dummy_brdf = std::make_shared<DummyBRDF>();
		std::shared_ptr<DiffuseBRDF> diffuse_brdf = std::make_shared<DiffuseBRDF>();
		std::shared_ptr<OrenNayarBRDF> oren_diffuse_brdf = std::make_shared<OrenNayarBRDF>();
	
		std::shared_ptr<DummyMaterial> light_material = std::make_shared<DummyMaterial>(glm::vec3(1.0f), glm::vec3(1.0f), dummy_brdf, dummy_brdf);
		std::shared_ptr<DiffuseMaterial> diffuse_ball_material = std::make_shared<DiffuseMaterial>(glm::vec3(0.5f), glm::vec3(0.0f), diffuse_brdf, dummy_brdf);
		std::shared_ptr<DiffuseMaterial> diffuse_oren_ball_material = std::make_shared<DiffuseMaterial>(glm::vec3(0.5f), glm::vec3(0.0f), oren_diffuse_brdf, dummy_brdf);
		
		//cealing material
		std::shared_ptr<DiffuseMaterial> ceiling_material = std::make_shared<DiffuseMaterial>(glm::vec3(0.32f, 0.31f, 0.33f), glm::vec3(0.0f), diffuse_brdf, dummy_brdf);
		//floor
		std::shared_ptr<DiffuseMaterial> floor_material = std::make_shared<DiffuseMaterial>(glm::vec3(0.31f, 0.31f, 0.32f), glm::vec3(0.0f), diffuse_brdf, dummy_brdf);
		//left wall
		std::shared_ptr<DiffuseMaterial> left_wall_material = std::make_shared<DiffuseMaterial>(glm::vec3(0.3f, 0.001f, 0.001f), glm::vec3(0.0f), diffuse_brdf, dummy_brdf);
		//right wall
		std::shared_ptr<DiffuseMaterial> right_wall_material = std::make_shared<DiffuseMaterial>(glm::vec3(0.001f, 0.3f, 0.001f), glm::vec3(0.0f), diffuse_brdf, dummy_brdf);
		//back wall
		std::shared_ptr<DiffuseMaterial> back_wall_material = std::make_shared<DiffuseMaterial>(glm::vec3(0.31f, 0.33f, 0.31f), glm::vec3(0.0f), diffuse_brdf, dummy_brdf);
		
		//std::shared_ptr<TransparentBRDF> transparent_brdf = std::make_shared<TransparentBRDF>();
		//Add light sources to both vectors, easier to compare if light was intersected
		std::shared_ptr<Plane> area_light1 = std::make_shared<Plane>(glm::vec3(5.0f, 14.99f, 5.0f), light_material, glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		std::shared_ptr<Plane> area_light2 = std::make_shared<Plane>(glm::vec3(-5.0f, 14.99f, 5.0f), light_material, glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		std::shared_ptr<Plane> area_light3 = std::make_shared<Plane>(glm::vec3(5.0f, 14.99f, -5.0f), light_material, glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		std::shared_ptr<Plane> area_light4 = std::make_shared<Plane>(glm::vec3(-5.0f, 14.99f, -5.0f), light_material, glm::vec3(0, -1, 0), 2.5f, 2.5f, 2.5f);
		scene.add_primitive(area_light1); scene.add_light_source(area_light1);
		scene.add_primitive(area_light2); scene.add_light_source(area_light2);
		scene.add_primitive(area_light3); scene.add_light_source(area_light3);
		scene.add_primitive(area_light4); scene.add_light_source(area_light4);
		//Add surfaces
		scene.add_primitive(std::make_shared<Sphere>(glm::vec3(9.0f, -10.0f, -5.0f), diffuse_oren_ball_material, 5.0f)); //Implicit surface
		scene.add_primitive(std::make_shared<Sphere>(glm::vec3(-9.0f, -10.0f, -5.0f), diffuse_ball_material, 5.0f)); //Implicit surface
		scene.add_primitive(std::make_shared<Sphere>(glm::vec3(-5.0f, -10.0f, 9.0f), diffuse_ball_material, 5.0f)); //Implicit surface

		//Add walls
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0.0f, 15.0f, 0.0f), ceiling_material, glm::vec3(0.0f, -1.0f, 0.0f))); //Ceiling plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0.0f, -15.0f, 0.0f), floor_material, glm::vec3(0.0f, 1.0f, 0.0f))); //Floor plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(-15.0f, 0.0f, 0.0f), left_wall_material, glm::vec3(1.0f, 0.0f, 0.0f))); //Left plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(15.0f, 0.0f, 0.0f), right_wall_material, glm::vec3(-1.0f, 0.0f, 0.0f))); //Right plane
		scene.add_primitive(std::make_shared<Plane>(glm::vec3(0.0f, 0.0f, 15.0f), back_wall_material, glm::vec3(0.0f, 0.0f, -1.0f))); //Back plane
	}
};