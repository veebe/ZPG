#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "TransformationComposite.h"
#include "TransformationRotate.h"
#include "TransformationScale.h"
#include "TransformationTranslate.h"
#include "Camera.h"

class DrawableObject {
public:
	DrawableObject(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation, Camera* ACamera);
	void DrawObject();
	void InitMatrixes();
	void AddLight(Light* ALight);
private:
	Model* model;
	ShaderProgram* shaderprogram;
	TransformationComposite* transformation;
	Camera* camera;
};