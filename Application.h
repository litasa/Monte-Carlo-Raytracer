#pragma once
#include <iostream>
#include <string>
#include "TgaWriter.h"
#include "PixelBuffer.h"
#include "Scene.h"
#include "SceneBuilder.h"
#include "Camera.h"
///When an application object is instatiated it immediately begins to build up a pixel buffer,
///setting up a camera and start rendering the scene with the given arguments.
///When the pixel buffer is ready it is written to an image.
class Application {
public:
	Application(unsigned int screen_width, unsigned int screen_height, const std::string &file_name, 
		unsigned int rays_per_pixel, unsigned int shadow_rays, unsigned int max_recursion_depth) {
		//Initialize pixel buffer for use
		std::cout << "Initializing pixel buffer...\n";
		PixelBuffer buffer(screen_width, screen_height);
		buffer.init_pixel_buffer();
		std::cout << "Pixel buffer successfully initialized.\n" << std::flush;
		//Build our scene 
		std::cout << "Building scene...\n";
		Scene scene;
		SceneBuilder::build_cornell_box(scene);
		std::cout << "Scene building completed.\n" << std::flush;
		//Setup camera
		std::cout << "Setting up camera...\n";
		glm::vec3 origin(0, 0, -55);
		glm::vec3 look_at_point(0, 0, 1);
		glm::vec3 world_up(0, 1, 0);
		float fov = 45.0f;
		float near_plane_distance = 5.0f;
		Camera camera(origin, look_at_point, world_up, fov, near_plane_distance, rays_per_pixel, shadow_rays, max_recursion_depth);
		std::cout << "Camera setup completed.\n" << std::flush;
		//Render scene
		std::cout << "Starting scene rendering...\n";
		camera.render_scene(scene, buffer);
		std::cout << "Scene rendering completed\n" << std::flush;
		//If status of buffer is ok, proceed to writing buffer to image
		std::cout << "Writing image with buffer data...\n";
		TgaWriter writer;
		writer.write(file_name, buffer);
		std::cout << "Image was written successfully.\n" << std::flush;
	};
};