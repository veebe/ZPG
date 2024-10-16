#pragma once

#include "ShaderProgram.h"
#include <vector>

class Model {
public:
	Model();
	Model(std::vector<float> AModel);
	virtual void DrawModel();
private:
	std::vector<float> model;
protected:
	void BindVAO(GLuint AVBO);
	GLuint VAO;
};