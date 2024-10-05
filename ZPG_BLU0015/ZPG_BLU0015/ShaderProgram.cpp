#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const GLchar* AVertexShader, const GLchar* AFragmentShader) {
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &AVertexShader, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &AFragmentShader, NULL);
	glCompileShader(fragmentShader);
	
	SPID = glCreateProgram();
	glAttachShader(SPID, fragmentShader);
	glAttachShader(SPID, vertexShader);
	glLinkProgram(SPID);

	CheckShader();
}

void ShaderProgram::CheckShader() {
	GLint status;
	glGetProgramiv(SPID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(SPID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(SPID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		exit(EXIT_FAILURE);
	}
}


void ShaderProgram::UseShader(){
	glUseProgram(SPID);
}