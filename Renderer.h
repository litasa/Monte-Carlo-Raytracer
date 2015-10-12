#pragma once
#include "glm\glm.hpp"
#include "Scene.h"
#include "Ray.h"
///A renderer takes a scene and a ray computes the light for a pixel
class Renderer {
public:
	Renderer() = default;
	glm::vec3 compute_light(const Scene &scene, const Ray &ray) {
		for (auto it = scene.get_primitives().cbegin(); it != scene.get_primitives().cend(); ++it) {
			glm::vec3 hit_point = (*it)->intersection(ray);
			if (hit_point != (*it)->_no_intersection) {
				//if ((*it)->get_type() == Primitive::PrimitiveType::Plane) {
				//	return glm::vec3(1.0, 0.0, 0.0);
				//}
			
				//Color spheres red
				if ((*it)->get_type() == Primitive::PrimitiveType::Sphere) {
					return glm::vec3(0.0, 1.0, 0.0);
				}
			}
		}

		return glm::vec3(0);
	}
};