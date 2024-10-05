#pragma once

#include "ShaderProgram.h"
#include <vector>

class Model {
public:
	Model(std::vector<float> Amodel, ShaderProgram* ASP);
	void DrawModel();
private:
	ShaderProgram* shaderprogram;
	GLuint VAO;
	std::vector<float> model;
};