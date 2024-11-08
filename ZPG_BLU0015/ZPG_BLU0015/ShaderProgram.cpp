#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const GLchar* AVertexShader, const GLchar* AFragmentShader, bool AisFile) {

	if (!AisFile) {
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &AVertexShader, NULL);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &AFragmentShader, NULL);
		glCompileShader(fragmentShader);

		shaderProgramID = glCreateProgram();
		glAttachShader(shaderProgramID, fragmentShader);
		glAttachShader(shaderProgramID, vertexShader);
		glLinkProgram(shaderProgramID);

		CheckShader();
	}
	else {
		loadShader(AVertexShader, AFragmentShader);
	}
}

void ShaderProgram::CheckShader() {
	GLint status;
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgramID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		exit(EXIT_FAILURE);
	}
}

void ShaderProgram::AddCamera(Camera* ACamera) {
	this->camera = ACamera;
	this->camera->Attach(this);
	OnCameraChangedProjection();
	OnCameraChangedView();
}

void ShaderProgram::ClearLights() {
	this->lights.clear();
}

void ShaderProgram::AddLight(Light* ALight) {
	if (!ALight) return;

	for (auto* existingLight : lights) {
		if (existingLight == ALight) {
			return;
		}
	}

	lights.push_back(ALight);
	ALight->Attach(this);
	
	OnLightChangePosition();
	OnLightChangeColor();
	OnLightChangeStrength();
	UpdateLightSize();
}

void ShaderProgram::UseShader(){
	glUseProgram(shaderProgramID);
}

void ShaderProgram::DeleteShader() {
	ShaderLoader::deleteShader();
}

void ShaderProgram::ApplyMaterial(Material* AMaterial) {
	GLuint idObjectColor = glGetUniformLocation(this->shaderProgramID, "objectColor");
	if (idObjectColor == -1)
		exit;
	glProgramUniform3fv(this->shaderProgramID, idObjectColor, 1, glm::value_ptr(AMaterial->GetObjectColor()));

	GLuint idAmbient = glGetUniformLocation(this->shaderProgramID, "ambient");
	if (idAmbient == -1)
		exit;
	glProgramUniform3fv(this->shaderProgramID, idAmbient, 1, glm::value_ptr(AMaterial->GetAmbientColor()));

	GLuint idShininess = glGetUniformLocation(this->shaderProgramID, "shininess");
	if (idShininess == -1)
		exit;
	glProgramUniform1f(this->shaderProgramID, idShininess, AMaterial->GetShininess());
}

void ShaderProgram::ApplyTransformation(glm::mat4 M) {
	GLint idModelTransform = glGetUniformLocation(shaderProgramID, "modelMatrix");
	if (idModelTransform == -1)
		exit;
	glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
}

void ShaderProgram::OnCameraChangedView()
{
	GLuint idModelTransform = glGetUniformLocation(this->shaderProgramID, "viewMatrix");
	if (idModelTransform == -1)
		exit;
	glProgramUniformMatrix4fv(this->shaderProgramID, idModelTransform, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	GLint idCameraPosition = glGetUniformLocation(this->shaderProgramID, "cameraPosition");
	if (idCameraPosition == -1)
		exit;
	glProgramUniform3fv(this->shaderProgramID, idCameraPosition, 1, glm::value_ptr(camera->GetCameraPosition()));
}

void ShaderProgram::OnCameraChangedProjection()
{
	GLuint idModelTransform = glGetUniformLocation(this->shaderProgramID, "projectionMatrix");
	if (idModelTransform == -1)
		exit;
	glProgramUniformMatrix4fv(this->shaderProgramID, idModelTransform, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));

	GLint idCameraPosition = glGetUniformLocation(shaderProgramID, "cameraPosition");
	if (idCameraPosition == -1)
		exit;
	glProgramUniform3fv(this->shaderProgramID, idCameraPosition, 1, glm::value_ptr(camera->GetCameraPosition()));
}

void ShaderProgram::OnLightChangePosition() {
	for (int i = 0; i < lights.size(); i++) {

		char uniformName[32];
		std::snprintf(uniformName, sizeof(uniformName), "lights[%d].position", i);

		GLuint idLightPosition = glGetUniformLocation(this->shaderProgramID, uniformName);
		glProgramUniform3fv(this->shaderProgramID, idLightPosition, 1, glm::value_ptr(lights[i]->GetLightPosition()));
	}
}

void ShaderProgram::OnLightChangeColor() {
	for (int i = 0; i < lights.size(); i++) {
		char uniformName[32];
		std::snprintf(uniformName, sizeof(uniformName), "lights[%d].color", i);

		GLuint idLightColor = glGetUniformLocation(this->shaderProgramID, uniformName);
		glProgramUniform3fv(this->shaderProgramID, idLightColor, 1, glm::value_ptr(lights[i]->GetLightColor()));
	}
}

void ShaderProgram::OnLightChangeStrength() {
	for (int i = 0; i < lights.size(); i++) {
		char uniformName[32];
		std::snprintf(uniformName, sizeof(uniformName), "lights[%d].strength", i);

		GLuint idLightStrength = glGetUniformLocation(this->shaderProgramID, uniformName);
		glProgramUniform1f(this->shaderProgramID, idLightStrength, lights[i]->GetLightStrength());
	}
}

void ShaderProgram::UpdateLightSize() {
	GLuint idLightNumber = glGetUniformLocation(this->shaderProgramID, "numLights");
	glProgramUniform1i(this->shaderProgramID, idLightNumber, lights.size());
}

void ShaderProgram::OnUpdate(NotifyType ANotifyType) {
	switch (ANotifyType) {
	case VIEWMATRIX:
		OnCameraChangedView();
		break;
	case PROJECTIONMATRIX:
		OnCameraChangedProjection();
		break;
	case LIGHTPOS:
		OnLightChangePosition();
		break;
	case LIGHTCOLOR:
		OnLightChangeColor();
		break;
	default:
		break;
	}
}