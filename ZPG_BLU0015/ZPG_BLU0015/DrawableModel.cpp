#include "DrawableModel.h"


DrawableModel::DrawableModel(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation, Material* AMaterial)
			  :DrawableObject(ATransformation), model(Amodel), shaderprogram(ASP), material(AMaterial) {};

void DrawableModel::DrawObject() {
	this->shaderprogram->UseShader();
	this->shaderprogram->ApplyMaterial(this->material);
	this->shaderprogram->ApplyTransformation(this->transformation->GetTransformationMatrix());
	this->model->DrawModel();
};

void DrawableModel::ApplyLight(Light* ALight) {
	this->shaderprogram->AddLight(ALight);
}

void DrawableModel::ApplyCamera(Camera* ACamera) {
	this->shaderprogram->AddCamera(ACamera);
}

void DrawableModel::ClearLights() {
	this->shaderprogram->ClearLights();
}