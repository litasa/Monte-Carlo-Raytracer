#include <string>
#include <iostream>
#include <cstdlib>
#include "Application.h"

#define STATUS_OK 0
#define STATUS_ERROR -1
#define PROG_ARGS 3
#define NO_PROG_ARGS 1

#ifndef DEFAULT_WIDTH
#define DEFAULT_WIDTH 1024
#endif

#ifndef DEFAULT_HEIGHT
#define DEFAULT_HEIGHT 768
#endif

/// The program takes as arguments the width and height of the screen.
/// In the future perhaps it will be able to parse a scene description.
/// Happy raytracing!
/// Authors: Andreas Christoffer Larsson, Jakob Törmä Ruhl

int main(int argc, char *argv[]) {

	int w, h;
	if (argc == PROG_ARGS) {

		w = std::atoi(argv[1]);
		h = std::atoi(argv[2]);
		if (w < 0 || h < 0) {
			std::cout << "Arguments must be integers larger than zero. " << std::endl;
			return STATUS_ERROR;
		}
	}
	else if (argc == NO_PROG_ARGS) {
		std::cout << "Arguments are set to default values. " << std::endl;
		w = DEFAULT_WIDTH;
		h = DEFAULT_HEIGHT;
	}
	else {
		std::cout << "Wrong number of arguments. " << std::endl;
		return STATUS_ERROR;
	}

	Application application(w, h);

	std::cin.ignore(); //Too see output in console

	return STATUS_OK;
}
