#pragma once
/* Vratislav Blunar - BLU0015 */
#include "DrawableObject.h"

class DrawableModel : public DrawableObject {
public:
	DrawableModel(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation, Material* AMaterial);
	DrawableModel(const DrawableModel& ADrawableModel);

	void DrawObject() override;

	void ApplyLight(Light* ALight) override;
	void ApplyCamera(Camera* ACamera) override;
	void ClearLights() override;

	DrawableModel* clone() const;
protected:
	Model* model;
	ShaderProgram* shaderprogram;
	Material* material;
};