#include <iostream>
#include <algorithm>
#include "TgaWriter.h"
#include "glm\glm.hpp"

void TgaWriter::write(std::string fn) {
	
	std::vector<char> header = std::vector<char>();
	for (unsigned int i = 0; i < 18; ++i) {
		header.push_back(0);
	}

	header[2] = 2; //Uncompressed, true color
	header[12] = _px_buffer.get_width() & 0xFF;
	header[13] = (_px_buffer.get_width() >> 8) & 0xFF;
	header[14] = _px_buffer.get_height() & 0xFF;
	header[15] = (_px_buffer.get_height() >> 8) & 0xFF;
	header[16] = 24; //Bpp

	std::vector<char> bytes = std::vector<char>();
	for (unsigned int y = 0; y < _px_buffer.get_height(); ++y) {
		for (unsigned int x = 0; x < _px_buffer.get_width(); ++x) {
			glm::vec3 value = _px_buffer.get_pixel_at(x, y).get_rgb_color_value();
			char b = (char)(255.0f * value.b);
			char g = (char)(255.0f * value.g);
			char r = (char)(255.0f * value.r);

			bytes.push_back(b & 0xFF);
			bytes.push_back(g & 0xFF);
			bytes.push_back(r & 0xFF);
		}
	}

	std::ofstream file(fn, std::ios::binary);
	if (file.is_open()) {
		std::for_each(header.cbegin(), header.cend(), [&file](char c) { file << c; });
		std::for_each(bytes.cbegin(), bytes.cend(), [&file](char c) { file << c; });
	}
}