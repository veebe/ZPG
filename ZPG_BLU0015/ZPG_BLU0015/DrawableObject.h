#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

class DrawableObject {
public:
	DrawableObject(Model* Amodel, ShaderProgram* ASP, Transformation* ATransformation);
	void DrawObject();
	void ScaleObject(float s);
	void MoveObject(float x, float y, float z);
	void SpinObject(float x, float y, float z);
private:
	Model* model;
	ShaderProgram* shaderprogram;
	Transformation* transformation;
};