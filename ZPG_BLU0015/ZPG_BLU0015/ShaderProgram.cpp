#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const GLchar* AVertexShader, const GLchar* AFragmentShader, bool AisFile) {

	if (!AisFile) {
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
	else {
		ShaderLoader(AVertexShader, AFragmentShader, &SPID);
	}
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

void ShaderProgram::AddCamera(Camera* ACamera) {
	this->camera = ACamera;
	this->camera->Attach(this);
}

void ShaderProgram::AddLight(Light* ALight) {
	this->light = ALight;
	this->light->Attach(this);
	OnLightChangePosition();
	OnLightChangeColor();
}


void ShaderProgram::UseShader(){
	glUseProgram(SPID);
}

void ShaderProgram::DeleteShader() {
	glDeleteProgram(SPID);
}

void ShaderProgram::ApplyTransformation(glm::mat4 M) {
	GLint idModelTransform = glGetUniformLocation(SPID, "modelMatrix");
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);

	GLint idCameraPosition = glGetUniformLocation(SPID, "cameraPosition");
	glUniformMatrix4fv(idCameraPosition, 1, GL_FALSE, glm::value_ptr(camera->GetCameraPosition()));
}

void ShaderProgram::OnCameraChangedView()
{
	GLuint idModelTransform = glGetUniformLocation(this->SPID, "viewMatrix");
	if (idModelTransform == -1)
		exit;
	glProgramUniformMatrix4fv(this->SPID, idModelTransform, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
}

void ShaderProgram::OnCameraChangedProjection()
{
	GLuint idModelTransform = glGetUniformLocation(this->SPID, "projectionMatrix");
	if (idModelTransform == -1)
		exit;
	glProgramUniformMatrix4fv(this->SPID, idModelTransform, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));
}

void ShaderProgram::OnLightChangePosition() {
	GLuint idLightPosition = glGetUniformLocation(this->SPID, "lightPosition");
	if (idLightPosition == -1)
		exit;
	glProgramUniform3fv(this->SPID, idLightPosition, 1, glm::value_ptr(light->GetLightPosition()));
}

void ShaderProgram::OnLightChangeColor() {
	GLuint idLightPosition = glGetUniformLocation(this->SPID, "lightColor");
	if (idLightPosition == -1)
		exit;
	glProgramUniform3fv(this->SPID, idLightPosition, 1, glm::value_ptr(light->GetLightColor()));
}