#pragma once
#include "Pixel.h"
#include "Ray.h"

class Pixel {
public:
	Pixel() {}
	float get_rgb_color_value() { return 1.0; }
	bool pixel_ready() { return true; }
private:
	Ray ray;
};