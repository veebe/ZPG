#pragma once

#include "DrawableModel.h"

class DrawableLightModel : public DrawableModel {
public:
	DrawableLightModel(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation, Material* AMaterial, Light* ALight);

	void DrawObject();
private:
	Light* light;
};