#pragma once
#include <iterator>
#include <vector>
#include "Pixel.h"
#define DEFAULT_PXBUF_WIDTH 1024
#define DEFAULT_PXBUF_HEIGHT 768
/// A pixel buffer just contains an amount of pixels corresponding to the screen size.
class PixelBuffer {
public:
	PixelBuffer(unsigned int width = DEFAULT_PXBUF_WIDTH, unsigned int height = DEFAULT_PXBUF_HEIGHT) : _width(width), _height(height) { }
	bool pixel_buffer_ready() { return _ready; }
	unsigned int get_width() { return _width; }
	unsigned int get_height() { return _height; }
	const std::vector<std::vector<Pixel>> &get_pixels() const { return _pixels; }
	
	//Initialize all pixels in buffer to the empty pixel
	void init_pixel_buffer() {
		_pixels = std::vector<std::vector<Pixel>>(_height, std::vector<Pixel>(_width, Pixel()));
		_ready = true;
	}

	//Camera has access to PixelBuffer's private members
	friend class Camera;

private:
	bool _ready = false;
	unsigned int _width;
	unsigned int _height;
	std::vector<std::vector<Pixel>> _pixels;
};