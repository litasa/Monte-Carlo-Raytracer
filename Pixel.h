#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\random.hpp"
#include "Pixel.h"
#include "Ray.h"

class Pixel {
public:
	Pixel() = default;
	glm::vec3 get_rgb_color_value() const { return glm::vec3(glm::clamp(glm::gaussRand(0.5, 0.25),0.0,1.0), glm::clamp(glm::gaussRand(0.5, 0.25),0.0,1.0), glm::clamp(glm::gaussRand(0.5, 0.25),0.0, 1.0)); }
	bool pixel_ready() { return true; }
private:
	Ray ray;
};