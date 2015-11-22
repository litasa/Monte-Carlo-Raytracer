#include <string>
#include <iostream>
#include <cstdlib>
#include "Application.h"
//Program parameters
#define STATUS_OK 0
#define STATUS_ERROR -1
#define PROG_ARGS 3
#define NO_PROG_ARGS 1
//Program arguments
#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 128
#endif
#ifndef DEFAULT_HEIGHT
#define DEFAULT_HEIGHT 128
#endif
#ifndef DEFAULT_RAYS_PER_PIXEL
#define DEFAULT_RAYS_PER_PIXEL 128
#endif 
#ifndef DEFAULT_SHADOW_RAYS 
#define DEFAULT_SHADOW_RAYS 4
#endif
#ifndef DEFAULT_MAXIMUM_RECURSION_DEPTH
#define DEFAULT_MAXIMUM_RECURSION_DEPTH 1
#endif
#ifndef DEFAULT_FILE_NAME
#define DEFAULT_FILE_NAME "raytraced_image_OrenNayarTest.tga"
#endif
/// The program takes as arguments:
///	* Width of the image in pixels
/// * Height of the image in pixels
/// * Degree of supersampling, a power-of-two number
/// * Amount of shadow rays for direct illumination
/// * Maximum depth of path for indirect illumination
///
/// In the future it will maybe be able to parse a scene description.
/// Happy raytracing!
/// Authors: Andreas Christoffer Larsson, Jakob Törmä Ruhl
int main(int argc, char *argv[]) {
	int width, height, rays_per_pixel, shadow_rays, max_recursion_depth;
	std::string file_name;
	if (argc == PROG_ARGS) {
		//Try converting ascii to integers
		width = std::atoi(argv[1]);
		height = std::atoi(argv[2]);
		rays_per_pixel = std::atoi(argv[3]);
		shadow_rays = std::atoi(argv[4]);
		max_recursion_depth = std::atoi(argv[5]);
		if (width < 0 || height < 0 || rays_per_pixel < 0 || shadow_rays < 0 || max_recursion_depth < 0) {
			std::cout << "Arguments must be integers larger than zero. Aborting. " << std::endl;
			return STATUS_ERROR;
		}
	}
	else if (argc == NO_PROG_ARGS) {
		std::cout << "Arguments are set to default values. " << std::endl;
		width = DEFAULT_WIDTH;
		height = DEFAULT_HEIGHT;
		rays_per_pixel = DEFAULT_RAYS_PER_PIXEL;
		shadow_rays = DEFAULT_SHADOW_RAYS;
		max_recursion_depth = DEFAULT_MAXIMUM_RECURSION_DEPTH;
		file_name = DEFAULT_FILE_NAME;
	}
	else {
		std::cout << "Wrong number of arguments. Aborting. " << std::endl;
		return STATUS_ERROR;
	}

	Application application(width, height, file_name, rays_per_pixel, shadow_rays, max_recursion_depth);
	std::cout << "Press any key to exit." << std::endl;
	std::cin.ignore(); //Too see output in console

	return STATUS_OK;
	
}
