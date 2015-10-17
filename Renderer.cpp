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
	glm::vec3 estimated_radiance(0);
	glm::vec3 sample_point(0);
	glm::vec3 normal(intersection.object->get_normal_at(intersection.point));
	int nr_lights = static_cast<int>(_scene.get_light_sources().size());
	float light_probability = 1.0f / static_cast<float>(nr_lights);
	for (int i = 0; i < _shadow_rays; ++i) {
		int index = glm::linearRand(0, nr_lights - 1);
		std::shared_ptr<Primitive> light = _scene.get_light_sources().at(index);
		sample_point = light->uniform_random_sample();
		float probability = light_probability * light->uniform_pdf(); //Maybe something better?
		glm::vec3 brdf = intersection.object->_material->get_brdf_color_mult(normal, glm::normalize(sample_point - intersection.point), intersection.direction);
		_num_direct_rays++;
		estimated_radiance += light->_material->get_emitted() * brdf * radiance_transfer(intersection, light, sample_point) / probability;
	}
	return estimated_radiance / (float)_shadow_rays;
}

float Renderer::radiance_transfer(const Intersection &intersection, const std::shared_ptr<Primitive> &object, const glm::vec3 &sample_point) {
	float g = geometry_term(intersection.point, sample_point, intersection.object->get_normal_at(intersection.point), object->get_normal_at(sample_point));
	float v = visibility_term(intersection.point, glm::normalize(sample_point - intersection.point), object);
	return g * v;
}

glm::vec3 Renderer::compute_indirect_light(const Intersection &intersection, int depth) {
	glm::vec3 estimated_radiance(0);
	float russian_random = glm::linearRand(0.0f, 1.0f);
	float absorption = intersection.object->_material->get_brdf()->get_absorption();
	if (russian_random > absorption) {
		int nr_rays = (int)glm::linearRand(1.0f, 1.0f);
		for (int i = 0; i < nr_rays; ++i) {
			glm::vec3 surface_normal = intersection.object->get_normal_at(intersection.point);
			if (intersection.object->_material->get_brdf()->get_type() == BRDF::BRDFType::DIFFUSE) {
				glm::vec3 new_dir = compute_diffuse_ray(surface_normal);
				Ray new_ray(intersection.point, new_dir);
				Intersection new_intersection;
				new_intersection.direction = -new_dir;
				find_nearest(new_ray, new_intersection.distance, new_intersection.point, new_intersection.object);
				if (new_intersection.point != Primitive::_no_intersection)
				{
					glm::vec3 brdf = intersection.object->_material->get_brdf_color_mult(surface_normal, new_dir, intersection.direction);
					float dot = glm::max( glm::dot(surface_normal, new_dir), 0.0f);
					_num_indirect_rays++;
					estimated_radiance += compute_radiance(new_intersection, depth + 1) * brdf * dot * glm::two_pi<float>(); //PDF is two pi, uniform sampling
				}
			}
		}
		estimated_radiance /= (float)nr_rays;
	}

	return estimated_radiance / (1 - absorption); //Should be absorption coeff
}

float Renderer::geometry_term(const glm::vec3 &point_a, const glm::vec3 &point_b, const glm::vec3 &normal_a, const glm::vec3 &normal_b) {
	glm::vec3 dir = glm::normalize(point_b - point_a);
	float cos_a = glm::dot(glm::normalize(normal_a), dir);
	float cos_b = glm::dot(glm::normalize(normal_b), -dir);
	//Multiply with some scaling factor so that color isn't black all the time.
	return 100.0f * (cos_a * cos_b) / (glm::dot(point_b - point_a, point_b - point_a));
}

float Renderer::visibility_term(const glm::vec3 &from_point, const glm::vec3 &direction, const std::shared_ptr<Primitive> &primitive) {
	Intersection intersection;
	Ray ray(from_point, direction);
	find_nearest(ray, intersection.distance, intersection.point, intersection.object);
	return intersection.object.get() == primitive.get() ? 1.0f : 0.0f;
}

glm::vec3 Renderer::compute_diffuse_ray(const glm::vec3 normal) {
	int abort = 0;
	while (true)
	{
		glm::vec3 random_dir = glm::normalize(glm::sphericalRand(1.0f));
		if (glm::dot(random_dir, normal) > 0) {
			return random_dir;
		}

		abort++;
		if (abort > 500)
		{
			return random_dir;
		}
	}
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