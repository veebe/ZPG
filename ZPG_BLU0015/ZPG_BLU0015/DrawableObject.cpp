#include "DrawableObject.h"

DrawableObject::DrawableObject(TransformationComposite* ATransformation): transformation(ATransformation) {};

/*
DrawableObject::DrawableObject(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation) {
	this->model = Amodel;
	this->shaderprogram = ASP;
	this->transformation = ATransformation;
};

void DrawableObject::DrawObject() {
	this->shaderprogram->UseShader();
	this->shaderprogram->ApplyTransformation(this->transformation->GetTransformationMatrix());
	this->model->DrawModel();
};

void DrawableObject::ApplyLight(Light* ALight) {
	this->shaderprogram->AddLight(ALight);
}

void DrawableObject::ApplyCamera(Camera* ACamera) {
	this->shaderprogram->AddCamera(ACamera);
}*/