#pragma once
#include <string>
#include <fstream>
#include "PixelBuffer.h"
class TgaWriter {
public:
	TgaWriter() {}
	TgaWriter(const PixelBuffer &px_buffer) : _px_buffer(_px_buffer)  {}
	void set_buffer(const PixelBuffer &px_buffer) { _px_buffer = px_buffer; }
	void write(std::string fn);
private:
	PixelBuffer _px_buffer;
};
