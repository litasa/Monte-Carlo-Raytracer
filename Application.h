#pragma once
#include "TgaWriter.h"
#include "PixelBuffer.h"
class Application {
public:
	Application(unsigned int screen_width, unsigned int screen_height) : _screen_width(screen_width), _screen_height(screen_height), _buffer(_screen_width, _screen_height) {
		//Run application
	};
private:
	const unsigned int _screen_width;
	const unsigned int _screen_height;
	TgaWriter _writer;
	PixelBuffer _buffer;
};