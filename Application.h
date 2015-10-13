#pragma once
#include <iostream>
#include "TgaWriter.h"
#include "PixelBuffer.h"
#include "Scene.h"
#include "SceneBuilder.h"
#include "Camera.h"
///When an application object is instatiated it immediately begins to build up a pixel buffer, when the pixel buffer is ready it is written to an image.
class Application {
public:
	Application(unsigned int screen_width, unsigned int screen_height) : _screen_width(screen_width), _screen_height(screen_height), _buffer(_screen_width, _screen_height) {
		//Initialize pixel buffer for use
		std::cout << "Initializing pixel buffer... ";
		_buffer.init_pixel_buffer();
		std::cout << "Done" << std::endl;

		//Build our scene 
		std::cout << "Building scene...";
		SceneBuilder::build_cornell_box(_scene);
		std::cout << "Done" << std::endl;

		//Setup camera
		std::cout << "Setting up camera...";
		_camera = Camera(glm::vec3(0, 0, -50), glm::vec3(0,0,1), glm::vec3(0,1,0), 45.0f, 5.0f, 1);
		std::cout << "Done" << std::endl;

		//Render scene
		std::cout << "Rendering scene...";
		_camera.render_scene(_scene, _buffer);
		std::cout << "Done" << std::endl;

		//Set the resulting buffer to the writer
		std::cout << "Setting buffer to image writer...";
		_writer.set_buffer(_buffer);
		std::cout << "Done" << std::endl;

		//If status of buffer is ok, proceed to writing buffer to image
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
	Camera _camera;
	Scene _scene;
};