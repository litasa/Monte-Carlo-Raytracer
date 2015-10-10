#pragma once
#include <vector>
#include "Ray.h"
#ifndef DEFAULT_RAYS_PER_PIXEL
#define DEFAULT_RAYS_PER_PIXEL 1
#endif
/// A ray collection can be used for supersampling for our raytracer
class RayCollection {
public:
	RayCollection(const unsigned int rays = DEFAULT_RAYS_PER_PIXEL) : _rays(rays), _ray_collection(std::vector<Ray>(_rays, Ray())) {};
private:
	unsigned int _rays;
	std::vector<Ray> _ray_collection;
};