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
#include "Material.h"

class ShaderProgram : IObserver,public ShaderLoader {
public:
	ShaderProgram(const GLchar* AVertexShader, const GLchar* AFragmentShader, bool AisFile = true);

	void UseShader();
	void DeleteShader();

	void ApplyTransformation(glm::mat4 M);
	void ApplyMaterial(Material * AMaterial);
	
	void OnCameraChangedProjection();
	void OnCameraChangedView();
	void OnLightChangePosition();
	void OnLightChangeColor();
	void OnMaterialChange();

	void OnUpdate(NotifyType ANotifyType) override;

	void AddCamera(Camera* ACamera);
	void AddLight(Light* ALight);
	void AddMaterial(Material* AMaterial);
private:
	Camera* camera;
	Light* light;
	Material* material;
	void CheckShader();

};