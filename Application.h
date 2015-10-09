#pragma once
#include <iostream>
#include "TgaWriter.h"
#include "PixelBuffer.h"
///When an application object is instatiated it immediately begins to build up a pixel buffer, when the pixel buffer is ready it is written to an image.
class Application {
public:
	Application(unsigned int screen_width, unsigned int screen_height) : _screen_width(screen_width), _screen_height(screen_height), _buffer(_screen_width, _screen_height) {
		std::cout << "Initializing pixel buffer... ";
		_buffer.init_pixel_buffer();
		std::cout << "Done" << std::endl;

		std::cout << "Setting buffer to image writer...";
		_writer.set_buffer(_buffer);
		std::cout << "Done" << std::endl;

		std::cout << "Checking buffer status...";
		if (_buffer.pixel_buffer_ready()) {
			std::cout << "OK" << std::endl;
			std::cout << "Writing image with buffer data...";
			_writer.write("imagewritetest.tga");
			std::cout << "Completed" << std::endl;
		}
		else {
			std::cout << "Bad" << std::endl;
		}
	};
private:
	const unsigned int _screen_width;
	const unsigned int _screen_height;
	TgaWriter _writer;
	PixelBuffer _buffer;
};