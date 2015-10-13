#pragma once
#include "glm\glm.hpp"
#include "Scene.h"
#include "Ray.h"
///A renderer takes a scene and a ray computes the light for a pixel
class Renderer {
public:
	Renderer() = default;
	glm::vec3 compute_light(const Scene &scene, const Ray &ray) {

		float nearest_squared_dist = std::numeric_limits<float>().max();
		glm::vec3 nearest_hit_point = Primitive::_no_intersection;
		std::shared_ptr<Primitive> nearest_primitive;

		for (auto it = scene.get_primitives().cbegin(); it != scene.get_primitives().cend(); ++it) {
			glm::vec3 hit_point = (*it)->intersection(ray);
			if (hit_point != Primitive::_no_intersection) {
				//If squared distance to hit point is smaller than before
				float squared_distance = glm::dot(hit_point, hit_point);
				if (squared_distance < nearest_squared_dist) {
					nearest_squared_dist = squared_distance;
					nearest_hit_point = hit_point;
					nearest_primitive = (*it);
				}
			}
		}

		//If we have an intersection, check what type...
		if (nearest_primitive != nullptr) {
			float dot = glm::dot(glm::normalize(nearest_primitive->get_normal_at(nearest_hit_point)), glm::normalize(-ray._direction));
			return nearest_primitive->_material->get_color() * glm::max(0.0f, dot);
		}

		return glm::vec3(0);
	}
};