#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

class ShaderProgram : Observer {
public:
	ShaderProgram(const GLchar* AVertexShader, const GLchar* AFragmentShader);
	void UseShader();
	void DeleteShader();

	void ApplyTransformation(glm::mat4 M);
	void OnCameraChangedProjection() override;
	void OnCameraChangedView() override;

	void AddCamera(Camera* ACamera);
private:
	Camera* camera;
	GLuint SPID;
	void CheckShader();

};