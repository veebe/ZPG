#pragma once
/* Vratislav Blunar - BLU0015 */
#include "DrawableModel.h"

class DrawableModelTextured : public DrawableModel {
public:
	DrawableModelTextured(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation, Material* AMaterial, Texture * ATexture);

	void DrawObject() override;
	void ShowSkyCube(bool AShowSkyCube);
protected:
	Texture* texture;
};