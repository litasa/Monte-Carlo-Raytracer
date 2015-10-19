#pragma once
#include <memory>
#include <vector>
#include "Ray.h"
#include "Material.h"
///The Primitive is an abstract base class for other primitives. A primitive is basically any implicit surface. 
///It holds methods for intersection and probability as well as the surface material for the primitive.
class Primitive
{
public:
	virtual ~Primitive() {}
	//Every primitive has a position origin and a material
	Primitive(glm::vec3 position, std::shared_ptr<Material> material);
	//Returns the hit point of the intersection with the given ray
	virtual glm::vec3 intersection(const Ray &ray) = 0;
	//Gets the normal at a position on the surface
	virtual glm::vec3 get_normal_at(const glm::vec3 &position) = 0;
	//Returns the area of the primitive surface
	virtual float area() = 0;
	//Returns the uniform probability distribution function of points on the surface
	virtual float uniform_pdf() = 0;
	//Returns a uniform probability random sample point on the primitive surface
	virtual glm::vec3 uniform_random_sample() = 0;
	//Fills a vector with uniform random samples
	virtual void uniform_random_sample(int nr_samples, std::vector<glm::vec3> &samples) = 0;
	//A constant for that identifies a non intersection
	static const glm::vec3 _no_intersection;
	glm::vec3 _position;
	std::shared_ptr<Material> _material;

protected:
	Primitive() = default;
};