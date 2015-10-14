#pragma once
#include "glm\glm.hpp"
#include "Scene.h"
#include "Ray.h"
///A renderer takes a scene and a ray computes the light for a pixel
class Renderer {
public:
	Renderer() = default;
	glm::vec3 compute_light(const Scene &scene, const Ray &ray, const glm::vec3 camera_pos, int depth) {

		if (depth == 10 || ray._importance < 0.01f)
			return glm::vec3(0);

		float nearest_to_camera = std::numeric_limits<float>().max();
		glm::vec3 nearest_hit_point = Primitive::_no_intersection;
		std::shared_ptr<Primitive> nearest_primitive;

		for (auto it = scene.get_primitives().cbegin(); it != scene.get_primitives().cend(); ++it) {
			glm::vec3 hit_point = (*it)->intersection(ray);
			if (hit_point != Primitive::_no_intersection) {
				//If squared distance to hit point is smaller than before
				float distance_to_camera = glm::length(hit_point - camera_pos);
				if (distance_to_camera < nearest_to_camera) {
					nearest_to_camera = distance_to_camera;
					nearest_hit_point = hit_point;
					nearest_primitive = (*it);
				}
			}
		}

		//If we have an intersection, check what type...
		if (nearest_primitive != nullptr) {
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
				glm::vec3 normal = glm::normalize(nearest_primitive->get_normal_at(nearest_hit_point));
				glm::vec3 refl = 2.0f * normal * (glm::dot(-ray._direction, normal)) - (-ray._direction);
				float dot = glm::dot(normal, refl);
				Ray new_ray(nearest_hit_point, glm::normalize(refl));
				new_ray._importance = 0.9f * ray._importance;
				return nearest_primitive->_material->get_color() + 2.0f * nearest_primitive->_material->_reflective * glm::max(0.0f, dot) * compute_light(scene, new_ray, camera_pos, depth + 1);
			}
		}

		return glm::vec3(0);
	}
};