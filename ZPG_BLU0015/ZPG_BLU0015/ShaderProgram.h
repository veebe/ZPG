#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>

class ShaderProgram {
public:
	ShaderProgram(const GLchar* AVertexShader, const GLchar* AFragmentShader);
	void UseShader();
	void CheckShader();
private:
	GLuint SPID;

};