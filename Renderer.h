#pragma once
#include "glm\glm.hpp"
#include "Scene.h"
#include "Ray.h"
///A renderer takes a scene and a ray computes the light for a pixel
class Renderer {
public:
	Renderer() = default;
	glm::vec3 compute_light(const Scene &scene, const Ray &ray, int depth) {

		if (depth == 25 || ray._importance < 0.001f)
			return glm::vec3(0);

		//Find the nearest intersection point and its primitive
		float nearest_distance;
		glm::vec3 nearest_point;
		std::shared_ptr<Primitive> nearest_primitive;
		find_nearest(scene, ray, nearest_distance, nearest_point, nearest_primitive);
		//If we have an intersection
		if (nearest_primitive != nullptr) {
			
			if (check_visibility(scene, nearest_point + 0.001f * nearest_primitive->get_normal_at(nearest_point))) {
				//we can now see the lightsource directly from where we stand.
				if (nearest_primitive->_material->_reflective >= 1.0f)
				{
					//TODO: Pure reflective materia (SHINY)
				}
				else if (nearest_primitive->_material->_refractive >= 1.0f)
				{
					//TODO: Pure refractive materia (I CAN SEE YOUR HOME FROM HERE)
				}
				else //Handle it as a diffuse
				{
					if (nearest_primitive->_material->_light) {
						return nearest_primitive->_material->get_color();
					}
					else {
						glm::vec3 directLight = nearest_primitive->_material->get_color(); //this line should be removed
						//glm::vec3 directLight = CalculateDirectLight();					//this line should be added
						glm::vec3 indirectLight = CalculateIndirectLight(nearest_point);
						//glm::vec3 normal = glm::normalize(nearest_primitive->get_normal_at(nearest_point));
						//glm::vec3 refl = glm::normalize(2.0f * normal * glm::dot(glm::normalize(ray._direction), normal) - glm::normalize(ray._direction));
						//float dot = glm::dot(normal, glm::normalize(scene.get_light_sources()[0]->_position - nearest_point));
						//Ray new_ray(nearest_point, refl);
						//new_ray._importance = 0.9f * ray._importance;
						return directLight + indirectLight; // +0.1f*compute_light(scene, new_ray, depth + 1);
					}
				}
			}
			else { //Handle indirect Light here too.
				return glm::vec3(0);
			}
		}
		return glm::vec3(0);
	}

	glm::vec3 CalculateIndirectLight(glm::vec3 hitpoint)
	{
		//for the number of indirect rays XXX (a number we decide or randomize)
		//take a random direction on the hemisphere, that will be our random_direction
		// (Jakob note) This should NOT BE TOWARDS A LIGHTSOURCE (/end)
		// Ray new_ray = new Ray(hitpoint, random_direction)
		// glm::vec3 next_iter = compute_light(scene, new_ray, depth +1);
		// glm::vec3 estimateRadiance = next_iter * brdf * cos(hitpoint._normal, random_direction) / pdf(random_direction);
		// return estimateRadiance /(XXX * ( 1 - absorption));
		return glm::vec3(0);
	}

	glm::vec3 CalculateDirectLight(glm::vec3 hitpoint, std::shared_ptr<Primitive> lightsource)
	{
		
		//generate random point on the light source called y, do this XXX times (we choose the number of times)
		//glm::vec3 estimateRadiance = lightsource->_material->get_color() * BRDF * G(hitpoint,y) / pdf(y);
		//estimateRadiance =/ XXX;
	}

	//the geometry term. Advanced Global Illumination page 43.
	float G(glm::vec3 point_a, glm::vec3 point_b, glm::vec3 normal_a, glm::vec3 normal_b)
	{
		glm::vec3 dir = point_b - point_a;
		float cosA = glm::dot(normal_a, dir) / (glm::length(dir) * glm::length(normal_a));
		float cosB = glm::dot(normal_b, -dir) / (glm::length(-dir) * glm::length(normal_b));

		return (cosA*cosB) / glm::dot(dir, dir);
	}

	void find_nearest(const Scene &scene, const Ray &ray, float &nearest_distance, glm::vec3 &nearest_point, std::shared_ptr<Primitive> &nearest_primitive) {
		nearest_distance = std::numeric_limits<float>().max();
		nearest_point = Primitive::_no_intersection;
		nearest_primitive = nullptr;
		//Search the scene geometry
		for (auto it = scene.get_primitives().cbegin(); it != scene.get_primitives().cend(); ++it) {
			glm::vec3 hit_point = (*it)->intersection(ray);
			if (hit_point != Primitive::_no_intersection) {
				//If squared distance to hit point is smaller than before
				float distance = glm::length(hit_point - ray._origin);
				if (distance < nearest_distance) {
					nearest_distance = distance;
					nearest_point = hit_point;
					nearest_primitive = (*it);
				}
			}
		}
	}


	//this function should check visability to all objects not only light
	bool check_visibility(const Scene &scene, const glm::vec3 &from_point) {
		for (auto it = scene.get_light_sources().cbegin(); it != scene.get_light_sources().cend(); ++it) {
			std::shared_ptr<Primitive> light = *it;
			if (light->get_type() == Primitive::PrimitiveType::Plane) {
				float nearest_distance;
				glm::vec3 nearest_point;
				std::shared_ptr<Primitive> nearest_primitive;
				find_nearest(scene, Ray(from_point, glm::normalize(light->_position - from_point)), nearest_distance, nearest_point, nearest_primitive);
				if (nearest_primitive.get() == light.get()) {
					return true;
				}
			}
		}
		return false;
	}
};

