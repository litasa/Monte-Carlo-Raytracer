#pragma once
#include <string>
#include "PixelBuffer.h"
/// This is a very simple TGA writing class, it takes a PixelBuffer and writes its contents to a file.
class TgaWriter {
public:
	TgaWriter() = default;
	//Takes the buffer with colors along with the file name to write to
	void write(const std::string &file_name, const PixelBuffer &buffer);
};
