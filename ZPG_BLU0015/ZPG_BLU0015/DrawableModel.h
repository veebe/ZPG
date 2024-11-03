#pragma once

#include "DrawableObject.h"

class DrawableModel : public DrawableObject {
public:
	DrawableModel(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation);

	void DrawObject() override;
	void ApplyLight(Light* ALight) override;
	void ApplyCamera(Camera* ACamera) override;
protected:
	Model* model;
	ShaderProgram* shaderprogram;
};