#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <ctime>
#include <random>

class Transformation {
public:
	Transformation();
	void Rotate(float x, float y, float z);
	void Scale(float scale);
	void Translate(float x, float y, float z);
	glm::mat4 GetTransformationMatrix();
private:
	glm::mat4 M;
};