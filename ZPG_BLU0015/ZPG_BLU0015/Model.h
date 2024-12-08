#pragma once
/* Vratislav Blunar - BLU0015 */
#include "ShaderProgram.h"
#include <vector>

class Model {
public:
	Model();
	Model(std::vector<float> AModel);
	virtual void DrawModel();
protected:
	virtual void BindVAO(GLuint AVBO);
	GLuint VAO = 0;
	std::vector<float> model;
};