#include "DrawableModel.h"


DrawableModel::DrawableModel(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation)
			  :DrawableObject(ATransformation), model(Amodel), shaderprogram(ASP) {};

void DrawableModel::DrawObject() {
	this->shaderprogram->UseShader();
	this->shaderprogram->ApplyTransformation(this->transformation->GetTransformationMatrix());
	this->model->DrawModel();
};

void DrawableModel::ApplyLight(Light* ALight) {
	this->shaderprogram->AddLight(ALight);
}

void DrawableModel::ApplyCamera(Camera* ACamera) {
	this->shaderprogram->AddCamera(ACamera);
}