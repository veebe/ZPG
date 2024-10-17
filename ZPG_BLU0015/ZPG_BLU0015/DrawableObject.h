#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "Camera.h"

class DrawableObject {
public:
	DrawableObject(Model* Amodel, ShaderProgram* ASP, Transformation* ATransformation, Camera* ACamera);
	void DrawObject();
	void ScaleObject(float s);
	void MoveObject(float x, float y, float z);
	void SpinObject(float x, float y, float z);
	void InitMatrixes();
private:
	Model* model;
	ShaderProgram* shaderprogram;
	Transformation* transformation;
	Camera* camera;
};