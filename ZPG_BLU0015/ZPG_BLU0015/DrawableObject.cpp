#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation, Camera* ACamera) {
	this->model = Amodel;
	this->shaderprogram = ASP;
	this->transformation = ATransformation;
	this->camera = ACamera;

	InitMatrixes();
};

void DrawableObject::InitMatrixes() {
	this->shaderprogram->AddCamera(this->camera);
	this->shaderprogram->OnCameraChangedView();
	this->shaderprogram->OnCameraChangedProjection();
}

void DrawableObject::DrawObject() {

	this->shaderprogram->UseShader();
	this->shaderprogram->ApplyTransformation(transformation->GetTransformationMatrix());
	this->model->DrawModel();
	
	//this->shaderprogram->DeleteShader();
};