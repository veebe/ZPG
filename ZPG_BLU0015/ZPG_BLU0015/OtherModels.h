#pragma once

#include "vector"

std::vector<float> plane = {
	-1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f,

	 -1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,
	 -1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f,
	  1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f
};

std::vector<float> triangle = {
	-1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
	 1.0f, 1.0f,  0.0f,   0.0f, 1.0f, 0.0f
};