#include <string>
#include <iostream>
#include <cstdlib>
#include "Application.h"
#define STATUS_OK 0
#define STATUS_ERROR -1
#define PROG_ARGS 3

/// The program takes as arguments the width and height of the screen.
/// In the future perhaps it will be able to parse a scene description.
/// Happy raytracing!
/// Authors: Andreas Christoffer Larsson, Jakob Törmä Ruhl

int main(int argc, char *argv[])
{
	if (argc != PROG_ARGS) {
		std::cout << "Wrong number of arguments. " << std::endl;
		return STATUS_ERROR;
	}
	else {

		int w = std::atoi(argv[1]), h = std::atoi(argv[2]);
		if (w < 0 || h < 0) {
			std::cout << "Arguments must be integers larger than zero. ";
			return STATUS_ERROR;
		}

		//Start application
		Application application();
	}

	return STATUS_OK;
}
