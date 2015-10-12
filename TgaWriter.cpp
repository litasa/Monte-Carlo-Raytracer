#include <iostream>
#include <iterator>
#include <cstdio>
#include <chrono>
#include <algorithm>
#include <functional>
#include "TgaWriter.h"
#include "glm\glm.hpp"

void TgaWriter::write(std::string file_name) {
	
	std::vector<char> header = std::vector<char>(18, 0);
	header[2] = 2; //Uncompressed, true color
	header[12] = _px_buffer.get_width() & 0xFF;
	header[13] = (_px_buffer.get_width() >> 8) & 0xFF;
	header[14] = _px_buffer.get_height() & 0xFF;
	header[15] = (_px_buffer.get_height() >> 8) & 0xFF;
	header[16] = 24; //Bpp

	//Loop over the pixel buffer and extract color values, these are mapped from 0.0..1.0 to 0..255
	std::vector<char> bytes = std::vector<char>();
	for (auto y_it = _px_buffer.get_pixels().cbegin(); y_it != _px_buffer.get_pixels().cend(); ++y_it) {
		for (auto x_it = (*y_it).begin(); x_it != (*y_it).cend(); ++x_it) {
			glm::vec3 color = (*x_it).get_rgb_color_value();
			bytes.push_back((char)(255.0f * color.b) & 0xFF);
			bytes.push_back((char)(255.0f * color.g) & 0xFF);
			bytes.push_back((char)(255.0f * color.r) & 0xFF);
		}
	}

	//Write the header and the content
	std::ofstream file(file_name, std::ios::binary);
	if (file.is_open()) {
		std::ostream_iterator<char> out(file);
		std::copy(header.cbegin(), header.cend(), out);
		std::copy(bytes.cbegin(), bytes.cend(), out);
	}
}

