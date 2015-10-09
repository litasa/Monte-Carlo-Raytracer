#pragma once
#include <iterator>
#include <vector>
#include "Pixel.h"

#define DEFAULT_PXBUF_WIDTH 1024
#define DEFAULT_PXBUF_HEIGHT 768

class PixelBuffer {
public:
	PixelBuffer(unsigned int width = DEFAULT_PXBUF_WIDTH, unsigned int height = DEFAULT_PXBUF_HEIGHT) : _width(width), _height(height) { }
	PixelBuffer(const PixelBuffer &pixel_buffer) : _width(pixel_buffer._width), _height(pixel_buffer._height), _pixels(pixel_buffer._pixels) { }
	PixelBuffer &operator=(const PixelBuffer &pixel_buffer) { _pixels = pixel_buffer._pixels;  return *this; }
	bool pixel_buffer_ready() { return true; }
	unsigned int get_width() { return _width; }
	unsigned int get_height() { return _height; }
	const Pixel &get_pixel_at(unsigned int x, unsigned int y) const { return _pixels.at(y).at(x); };

	void init_pixel_buffer() {
		for (unsigned int y = 0; y < _height; ++y) {
			std::vector<Pixel> pixel_row;
			for (unsigned int x = 0; x < _width; ++x) {
				pixel_row.push_back(Pixel());
			}	
			_pixels.push_back(pixel_row);
		}
	}

private:
	const unsigned int _width;
	const unsigned int _height;
	std::vector<std::vector<Pixel>> _pixels;
};