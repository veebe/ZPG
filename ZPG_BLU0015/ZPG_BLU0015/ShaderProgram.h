#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
public:
	ShaderProgram(const GLchar* AVertexShader, const GLchar* AFragmentShader);
	void UseShader();
	void DeleteShader();

	void ApplyTransformation(glm::mat4 M);
	void ApplyProjection(glm::mat4 M);
	void ApplyView(glm::mat4 M);

private:
	GLuint SPID;
	void CheckShader();

};