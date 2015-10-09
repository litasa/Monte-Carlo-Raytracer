#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\random.hpp"
#include "Pixel.h"
#include "Ray.h"
/// A pixel can be seen as a representation of the camera's near plane. Each contains one or more Rays that was sent from the eye into the scene.
class Pixel {
public:
	Pixel() = default;
	bool pixel_ready() { return true; }
	
	//For testing purposes this method returns a gaussian random distribution color
	glm::vec3 get_rgb_color_value() const {
		return glm::vec3(glm::clamp(glm::gaussRand(0.5, 0.25), 0.0, 1.0),
			glm::clamp(glm::gaussRand(0.5, 0.25), 0.0, 1.0),
			glm::clamp(glm::gaussRand(0.5, 0.25), 0.0, 1.0));
	}

private:
	Ray ray;
};