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
	glm::vec3 get_rgb_color_value() const { return _rgb_color; }
	void set_rgb_color_value(const glm::vec3 &rgb_color) { _rgb_color = rgb_color; }
private:
	glm::vec3 _rgb_color;
};