#include <fstream>
#include "TgaWriter.h"
#include "glm\glm.hpp"

void TgaWriter::write(const std::string &file_name, const PixelBuffer &buffer) {
	
	std::vector<char> header = std::vector<char>(18, 0);
	header[2] = 2; //Uncompressed, true color
	header[12] = buffer.get_width() & 0xFF;
	header[13] = (buffer.get_width() >> 8) & 0xFF;
	header[14] = buffer.get_height() & 0xFF;
	header[15] = (buffer.get_height() >> 8) & 0xFF;
	header[16] = 24; //Bpp

	//Loop over the pixel buffer and extract color values, these are mapped from 0.0..1.0 to 0..255
	std::vector<char> bytes = std::vector<char>();
	for (unsigned int y = 0; y < buffer.get_height(); ++y) {
		for (unsigned int x = 0; x < buffer.get_width(); ++x) {
			const glm::vec3 &color = buffer.get_rgb_color(x, y);
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

