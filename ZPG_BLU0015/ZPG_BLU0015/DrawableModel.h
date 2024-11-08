#pragma once

#include "DrawableObject.h"

class DrawableModel : public DrawableObject {
public:
	DrawableModel(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation, Material* AMaterial);

	void DrawObject() override;

	void ApplyLight(Light* ALight) override;
	void ApplyCamera(Camera* ACamera) override;
	void ClearLights() override;
protected:
	Model* model;
	ShaderProgram* shaderprogram;
	Material* material;
};