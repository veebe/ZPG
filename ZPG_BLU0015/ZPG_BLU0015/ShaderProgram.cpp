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

void ShaderProgram::AddLight(Light* ALight) {
	this->light = ALight;
	if (this->light) {
		this->light->Attach(this);
	}
	OnLightChangePosition();
	OnLightChangeColor();
	
}

void ShaderProgram::AddMaterial(Material* AMaterial) {
	this->material = AMaterial;
	this->material->Attach(this);
	OnMaterialChange();
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

	GLint idCameraPosition = glGetUniformLocation(shaderProgramID, "cameraPosition");
	if (idCameraPosition == -1)
		exit;
	glUniformMatrix4fv(idCameraPosition, 1, GL_FALSE, glm::value_ptr(camera->GetCameraPosition()));
}

void ShaderProgram::OnCameraChangedView()
{
	GLuint idModelTransform = glGetUniformLocation(this->shaderProgramID, "viewMatrix");
	if (idModelTransform == -1)
		exit;
	glProgramUniformMatrix4fv(this->shaderProgramID, idModelTransform, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
}

void ShaderProgram::OnCameraChangedProjection()
{
	GLuint idModelTransform = glGetUniformLocation(this->shaderProgramID, "projectionMatrix");
	if (idModelTransform == -1)
		exit;
	glProgramUniformMatrix4fv(this->shaderProgramID, idModelTransform, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));
}

void ShaderProgram::OnLightChangePosition() {
	GLuint idLightPosition = glGetUniformLocation(this->shaderProgramID, "lightPosition");
	if (idLightPosition == -1)
		exit;
	if(this->light)
		glProgramUniform3fv(this->shaderProgramID, idLightPosition, 1, glm::value_ptr(light->GetLightPosition()));
	else
		glProgramUniform3fv(this->shaderProgramID, idLightPosition, 1, glm::value_ptr(glm::vec3(0,0,0)));
}

void ShaderProgram::OnLightChangeColor() {
	GLuint idLightPosition = glGetUniformLocation(this->shaderProgramID, "lightColor");
	if (idLightPosition == -1)
		exit;
	if (this->light)
		glProgramUniform3fv(this->shaderProgramID, idLightPosition, 1, glm::value_ptr(light->GetLightColor()));
	else
		glProgramUniform3fv(this->shaderProgramID, idLightPosition, 1, glm::value_ptr(glm::vec3(0,0,0)));

}

void ShaderProgram::OnMaterialChange() {
	ApplyMaterial(this->material);
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
	case MATERIAL:
		OnMaterialChange();
		break;
	default:
		break;
	}
}