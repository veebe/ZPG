#include "DrawableLightModel.h"

DrawableLightModel::DrawableLightModel(Model* AModel, ShaderProgram* ASP, TransformationComposite* ATransformation, Material* AMaterial, Light* ALight)
	:DrawableModel(AModel, ASP, ATransformation, AMaterial), light(ALight) {}

void DrawableLightModel::DrawObject() {
	this->light->SetLightPostion(glm::vec3(this->transformation->GetTransformationMatrix()[3]));
	DrawableModel::DrawObject();
};