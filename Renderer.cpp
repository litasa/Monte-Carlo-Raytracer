#include "Renderer.h"
#include "glm\gtc\constants.hpp"
#include "glm\gtc\random.hpp"

glm::vec3 Renderer::radiance(const Ray &ray) {
	//Find the nearest intersection point and its primitive
	Intersection intersection;
	find_nearest(ray, intersection.distance, intersection.point, intersection.object);
	//If we have an intersection
	if (intersection.object != nullptr) {
		//Light travels to the eye
		intersection.direction = -ray._direction;
		return intersection.object->_material->get_emitted() + compute_radiance(intersection, 0);
	}
	//Black if no intersection
	return glm::vec3(0);
}

glm::vec3 Renderer::compute_radiance(const Intersection &intersection, int depth) {
	glm::vec3 estimated_radiance;
	estimated_radiance += compute_direct_light(intersection);
	estimated_radiance += compute_indirect_light(intersection, depth);

	return estimated_radiance;
}

glm::vec3 Renderer::compute_direct_light(const Intersection &intersection) {
	glm::vec3 estimated_radiance;
	int nr_lights = static_cast<int>(_scene.get_light_sources().size());
	for (int i = 0; i < _shadow_rays; ++i) {
		int index = glm::linearRand(0, nr_lights - 1);
		std::shared_ptr<Primitive> light = _scene.get_light_sources().at(index);
		glm::vec3 sample_point = light->_position; //No random sampling, yet.
		float probability = probability_distribution(light) * probability_distribution(light, sample_point);
		estimated_radiance += light->_material->get_emitted() * intersection.object->_material->get_color() * radiance_transfer(intersection, light, sample_point) / probability; //NO BRDF YET
	}
	return estimated_radiance; // (float)_shadow_rays; //Division of #paths, need to change for indirect illumination
}

float Renderer::radiance_transfer(const Intersection &intersection, const std::shared_ptr<Primitive> &object, const glm::vec3 &sample_point) {
	float g = geometry_term(intersection.point, sample_point, intersection.object->get_normal_at(intersection.point), object->get_normal_at(sample_point));
	float v = visibility_term(intersection.point, glm::normalize(sample_point - intersection.point), object);
	return g * v;
}

float Renderer::probability_distribution(const std::shared_ptr<Primitive> &object, const glm::vec3 &point) {
	if (object->get_type() == Primitive::PrimitiveType::Plane)
	{
		Plane *plane = dynamic_cast<Plane*>(object.get());
		return 1.0f / plane->_area;
	}
	return 0.0f; //CHECK ZERO
}

float Renderer::probability_distribution(const std::shared_ptr<Primitive> &object) {
	return 1.0f / _scene.get_light_sources().size(); //CHECK ZERO
}

glm::vec3 Renderer::compute_indirect_light(const Intersection &intersection, int depth) {
	glm::vec3 estimated_radiance(0);
	//int russian_roulette = (int)glm::linearRand(0.0f, 5.0f);
	if (depth < 2) {
		int nr_rays = (int)glm::linearRand(1.0f, 5.0f);
		for (int i = 0; i < nr_rays; ++i) {
			glm::vec3 surface_normal = intersection.object->get_normal_at(intersection.point);
			glm::vec3 new_dir = intersection.direction - 2.0f * (glm::dot(surface_normal, intersection.direction)) * surface_normal;
			Ray new_ray(intersection.point, new_dir);
			Intersection new_intersection;
			new_intersection.direction = -new_dir;
			find_nearest(new_ray, new_intersection.distance, new_intersection.point, new_intersection.object);
			bool no_light = true;
			for (auto it = _scene.get_light_sources().cbegin(); it != _scene.get_light_sources().cend(); ++it) {
				if (new_intersection.object.get() == (*it).get()) {
					no_light = false;
				}
			}

			if (no_light) {
				estimated_radiance += compute_radiance(new_intersection, depth + 1) * intersection.object->_material->get_color() * glm::dot(intersection.object->get_normal_at(intersection.point), new_dir) / glm::pi<float>(); //Should have PDF, now just pi
				//if (glm::length(estimated_radiance) != 0) {
				//	std::cout << "COLOR!!" << std::endl;
				//}
			}
		}

		//estimated_radiance /= (float)nr_rays; //Should be #paths
	}

	return estimated_radiance / 1.0f; //Should be absorption coeff
}

float Renderer::geometry_term(const glm::vec3 &point_a, const glm::vec3 &point_b, const glm::vec3 &normal_a, const glm::vec3 &normal_b) {
	glm::vec3 dir = glm::normalize(point_b - point_a);
	float cos_a = glm::dot(glm::normalize(normal_a), dir);
	float cos_b = glm::dot(glm::normalize(normal_b), -dir);
	return (cos_a * cos_b) / (glm::dot(point_b - point_a, point_b - point_a));
}

float Renderer::visibility_term(const glm::vec3 &from_point, const glm::vec3 &direction, const std::shared_ptr<Primitive> &primitive) {
	Intersection intersection;
	Ray ray(from_point, direction);
	find_nearest(ray, intersection.distance, intersection.point, intersection.object);
	return intersection.object.get() == primitive.get() ? 1.0f : 0.0f;
}

void Renderer::find_nearest(const Ray &ray, float &nearest_distance, glm::vec3 &nearest_point, std::shared_ptr<Primitive> &nearest_primitive) {
	nearest_distance = std::numeric_limits<float>().max();
	nearest_point = Primitive::_no_intersection;
	nearest_primitive = nullptr;
	//Search the scene geometry
	for (auto it = _scene.get_primitives().cbegin(); it != _scene.get_primitives().cend(); ++it) {
		glm::vec3 hit_point = (*it)->intersection(ray);
		if (hit_point != Primitive::_no_intersection) {
			//Account for self intersection
			hit_point += 0.0001f * (*it)->get_normal_at(hit_point);
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