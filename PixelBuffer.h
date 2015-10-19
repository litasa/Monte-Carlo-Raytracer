#pragma once
#include <iterator>
#include <vector>
#include "glm\glm.hpp"
/// A pixel buffer just contains an amount of pixels corresponding to the screen size.
/// A pixel is simply represented as a RGB color value.
class PixelBuffer {
public:
	PixelBuffer(unsigned int width = 0, unsigned int height = 0) : _width(width), _height(height) { }
	//Getters for image dimensions
	unsigned int get_width() const { return _width; }
	unsigned int get_height() const { return _height; }
	//Set the pixel color value, has no bounds check so make sure it's properly initialized
	void set_rgb_value(unsigned int x, unsigned int y, const glm::vec3 &color) {
		_pixels[y][x] = color;
	}
	//Getter for pixel color, has no bounds check so make sure it's properly initialized
	const glm::vec3 &get_rgb_color(unsigned int x, unsigned int y) const {
		return _pixels[y][x];
	}
	//Initialize all pixels in buffer to the empty pixel
	void init_pixel_buffer() {
		_pixels.reserve(_height);
		for (unsigned int y = 0; y < _height; ++y) {
			std::vector<glm::vec3> row;
			row.reserve(_width);
			for (unsigned int x = 0; x < _width; ++x) {
				row.push_back(glm::vec3(0));
			}
			_pixels.push_back(row);
		}
		_ready = true;
	}
private:
	bool _ready = false;
	unsigned int _width, _height;
	typedef std::vector<std::vector<glm::vec3>> image_t;
	image_t _pixels;
};