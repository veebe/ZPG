#include "DrawableLightModel.h"

DrawableLightModel::DrawableLightModel(Model* AModel, ShaderProgram* ASP, TransformationComposite* ATransformation, Light* ALight)
	:DrawableModel(AModel, ASP, ATransformation), light(ALight) {}

void DrawableLightModel::DrawObject() {
	this->light->SetLightPostion(glm::vec3(this->transformation->GetTransformationMatrix()[3]));
	DrawableModel::DrawObject();
};