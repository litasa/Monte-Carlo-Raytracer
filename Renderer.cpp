#include "Renderer.h"
#include "glm\gtc\constants.hpp"
#include "glm\gtc\random.hpp"

glm::vec3 Renderer::radiance(const Ray &ray) {
	//Find the nearest intersection point and its primitive
	Intersection intersection;
	find_nearest(ray, intersection);
	//If we have an intersection
	if (intersection._object != nullptr) {
		//Light travels to the eye
		intersection._radiance_direction = -ray._direction;
		return intersection._object->_material->get_emitted() + compute_radiance(intersection, 0);
	}
	//Black if no intersection
	return glm::vec3(0);
}

glm::vec3 Renderer::compute_radiance(const Intersection &intersection, int depth) {
	//This is the recursive function that'll be called for each ray intersection
	glm::vec3 estimated_radiance;
	estimated_radiance += compute_direct_light(intersection);
	estimated_radiance += compute_indirect_light(intersection, depth);
	return estimated_radiance;
}

glm::vec3 Renderer::compute_direct_light(const Intersection &intersection) {
	glm::vec3 estimated_radiance, sample_point, normal = intersection.get_normal();
	std::shared_ptr<Primitive> light;
	std::shared_ptr<Material> material = intersection._object->_material;
	//The number of shadow rays increases shadow quality
	for (int i = 0; i < _shadow_rays; ++i) {
		//Choose a random light and sample a point on its surface uniformly
		light = _scene.get_light_sources()[glm::linearRand(0, _light_count - 1)];
		sample_point = light->uniform_random_sample();
		float probability = _light_probability * light->uniform_pdf(); //Maybe something better?
		//The BRDF determines the probability of the outgoing radiance in this point in our radiance direction.
		glm::vec3 brdf = material->get_brdf_color_mult(normal, glm::normalize(sample_point - intersection._point), intersection._radiance_direction);
		estimated_radiance += light->_material->get_emitted() * brdf * radiance_transfer(intersection, light, sample_point) / probability;
	}
	//For debugging
	mutex.lock();
	_num_direct_rays += _shadow_rays;
	mutex.unlock();
	//Average results over the number of shadow rays, this will give soft shadows since non visible points won't contribute
	return estimated_radiance / (float)_shadow_rays;
}

float Renderer::radiance_transfer(const Intersection &intersection, const std::shared_ptr<Primitive> &object, const glm::vec3 &sample_point) {
	//The radiance transfer is just a collected term for G and V
	float g = geometry_term(intersection, sample_point, object->get_normal_at(sample_point));
	float v = visibility_term(intersection, sample_point, object); 
	return g * v;
}

glm::vec3 Renderer::compute_indirect_light(const Intersection &intersection, int depth) {
	glm::vec3 estimated_radiance;
	float russian_random = glm::linearRand(0.0f, 1.0f);
	std::shared_ptr<Material> material = intersection._object->_material;
	std::shared_ptr<BRDF> brdf = material->get_brdf();
	//Russian roulette and maximum recursion depth determines if we continue
	if (russian_random > brdf->get_absorption() && depth < _max_recursion_depth) {
		int rays = 1;// glm::linearRand(15, 20);
		for (int i = 0; i < rays; ++i) {
			glm::vec3 surface_normal = intersection.get_normal();
			//Check if we have a perfect diffuse reflector
			if (brdf->get_type() == BRDF::BRDFType::DIFFUSE || brdf->get_type() == BRDF::BRDFType::ORENDIFFUSE) {
				//Find a random direction on the hemisphere on the surface
				glm::vec3 diffuse_dir = compute_diffuse_ray(surface_normal);
				Ray indirect_ray(intersection._point, diffuse_dir);
				Intersection indirect(-diffuse_dir);
				find_nearest(indirect_ray, indirect);
				//If some object is transfering radiance to our intersection point
				if (indirect._point != Primitive::_no_intersection) {
					//The BRDF determines the probability of the outgoing radiance in this point in our radiance direction.
					//The dot product is the cos(theta) that determines how easily light is reflected in this point
					glm::vec3 brdf_contribution = material->get_brdf_color_mult(surface_normal, diffuse_dir, intersection._radiance_direction);
					estimated_radiance += compute_radiance(indirect, depth + 1) * brdf_contribution * glm::two_pi<float>(); //PDF is two pi, uniform sampling
				}
			}
		}
		//Take the average (Monte Carlo sampling)
		estimated_radiance /= (float)rays;
		//For debugging
		mutex.lock();
		_num_indirect_rays += rays;
		mutex.unlock();
	}

	//If there's a high absorption this estimated radiance will have large contribution to the final estimated radiance
	return estimated_radiance / (1.0f - brdf->get_absorption());
}

float Renderer::geometry_term(const Intersection &intersection, const glm::vec3 &point, const glm::vec3 &normal) {
	//For direct illumination this this basically gives us the projected solid angle onto the intersection point.
	glm::vec3 dir = glm::normalize(point - intersection._point);
	float cos_a = glm::dot(intersection.get_normal(), dir);
	float cos_b = glm::dot(normal, -dir);
	glm::vec3 distance = point - intersection._point;
	//Squared fall-off for lights
	return cos_a * cos_b / glm::dot(distance, distance);
}

float Renderer::visibility_term(const Intersection &intersection, const glm::vec3 &point, const std::shared_ptr<Primitive> &primitive) {
	//If the given primitive is the same as is intersected, it's visible.
	Ray ray(intersection._point, glm::normalize(point - intersection._point));
	Intersection visible;
	find_nearest(ray, visible);
	return visible._object == primitive ? 1.0f : 0.0f;
}

glm::vec3 Renderer::compute_diffuse_ray(const glm::vec3 normal) {
	//Sample point on the hemisphere, just reverse it if it's on the "negative" hemisphere. Gives something like a uniform distribution.
	glm::vec3 random_dir = glm::sphericalRand(1.0f);
	return glm::dot(random_dir, normal) > 0 ? random_dir : -random_dir;
}

void Renderer::find_nearest(const Ray &ray, Intersection &intersection) {
	intersection._distance =  _max_ray_distance;
	intersection._point = Primitive::_no_intersection;
	intersection._object = nullptr;
	//Search the scene geometry
	glm::vec3 hit_point;
	for (auto it = _scene.get_primitives().cbegin(); it != _scene.get_primitives().cend(); ++it) {
		hit_point = (*it)->intersection(ray);
		if (hit_point != Primitive::_no_intersection) {
			//Account for self intersection
			hit_point += _ray_epsilon * (*it)->get_normal_at(hit_point);
			//If squared distance to hit point is smaller than before
			float distance = glm::distance(hit_point, ray._origin);
			if (distance < intersection._distance) {
				intersection._distance = distance;
				intersection._point = hit_point;
				intersection._object = (*it);
			}
		}
	}
}