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
	if (this->camera != ACamera){
		this->camera = ACamera;
		this->camera->Attach(this);
		OnCameraChangedProjection();
		OnCameraChangedView();
	}
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
void ShaderProgram::UnUseShader() {
	glUseProgram(0);
}

void ShaderProgram::DeleteShader() {
	ShaderLoader::deleteShader();
}

void ShaderProgram::ApplyMaterial(Material* AMaterial) {
	SendVariableToShader("objectColor", AMaterial->GetObjectColor());
	SendVariableToShader("ambient", AMaterial->GetAmbientColor());
	SendVariableToShader("shininess", AMaterial->GetShininess());
}

void ShaderProgram::ApplyTexture(Texture* ATexture) {
	SendVariableToShader("textureUnitID", ATexture->GetTextureId());
	SendVariableToShader("UISky", ATexture->GetTextureId());
}

void ShaderProgram::ApplyTransformation(glm::mat4 M) {
	SendVariableToShader("modelMatrix", M);
}

void ShaderProgram::ShowSkyCube(bool AShowSkyCube) {
	SendVariableToShader("showSkyCube", AShowSkyCube);
}

void ShaderProgram::OnCameraChangedView()
{
	SendVariableToShader("viewMatrix", camera->GetViewMatrix());
	SendVariableToShader("cameraPosition", camera->GetCameraPosition());
	SendVariableToShader("cameraDirection", camera->GetCameraDirection());
}

void ShaderProgram::OnCameraChangedProjection()
{
	SendVariableToShader("projectionMatrix", camera->GetProjectionMatrix());
	SendVariableToShader("cameraPosition", camera->GetCameraPosition());
	SendVariableToShader("cameraDirection", camera->GetCameraDirection());
}

void ShaderProgram::OnLightChangePosition() {
	for (int i = 0; i < lights.size(); i++) {

		char uniformName[32];
		std::snprintf(uniformName, sizeof(uniformName), "lights[%d].position", i);

		if (lights[i]->GetLightType() == REFLECTOR)
			SendVariableToShader(uniformName, camera->GetCameraPosition());
		else
			SendVariableToShader(uniformName, lights[i]->GetLightPosition());
	}
}

void ShaderProgram::OnLightChangeColor() {
	for (int i = 0; i < lights.size(); i++) {
		char uniformName[32];
		std::snprintf(uniformName, sizeof(uniformName), "lights[%d].color", i);

		SendVariableToShader(uniformName, lights[i]->GetLightColor());
	}
}

void ShaderProgram::OnLightChangeStrength() {
	for (int i = 0; i < lights.size(); i++) {
		char uniformName[32];
		std::snprintf(uniformName, sizeof(uniformName), "lights[%d].strength", i);

		SendVariableToShader(uniformName, lights[i]->GetLightStrength());
	}
}

void ShaderProgram::UpdateLightSize() {
	SendVariableToShader("numLights", int(lights.size()));

	for (int i = 0; i < lights.size(); i++) {
		char uniformName[32];
		std::snprintf(uniformName, sizeof(uniformName), "lights[%d].type", i);

		SendVariableToShader(uniformName, lights[i]->GetLightType());
	}
}

void ShaderProgram::SendVariableToShader(const char* AName, glm::mat4 AValue) {
	if (GetUniLocation(AName))
		glProgramUniformMatrix4fv(this->shaderProgramID, idUniLocation, 1, GL_FALSE, glm::value_ptr(AValue));
}
void ShaderProgram::SendVariableToShader(const char* AName, glm::vec3 AValue) {
	if (GetUniLocation(AName))
		glProgramUniform3fv(this->shaderProgramID, idUniLocation, 1, glm::value_ptr(AValue));
}
void ShaderProgram::SendVariableToShader(const char* AName, float AValue) {
	if (GetUniLocation(AName))
		glProgramUniform1f(this->shaderProgramID, idUniLocation, AValue);
}
void ShaderProgram::SendVariableToShader(const char* AName, int AValue) {
	if (GetUniLocation(AName))
		glProgramUniform1i(this->shaderProgramID, idUniLocation, AValue);
}

bool ShaderProgram::GetUniLocation(const char* AName) {
	idUniLocation = glGetUniformLocation(shaderProgramID, AName);
	if (idUniLocation == -1)
		return false;
	return true;
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