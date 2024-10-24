#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "ShaderLoader.h"
#include "Light.h"

class ShaderProgram : IObserver, ShaderLoader {
public:
	ShaderProgram(const GLchar* AVertexShader, const GLchar* AFragmentShader, bool AisFile = true);

	void UseShader();
	void DeleteShader();

	void ApplyTransformation(glm::mat4 M);
	
	void OnCameraChangedProjection() override;
	void OnCameraChangedView() override;
	void OnLightChangePosition() override;
	void OnLightChangeColor() override;

	void AddCamera(Camera* ACamera);
	void AddLight(Light* ALight);
private:
	Camera* camera;
	Light* light;
	GLuint SPID;
	void CheckShader();

};