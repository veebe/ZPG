#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* Amodel, ShaderProgram* ASP, Transformation* ATransformation, Camera* ACamera) {
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
	this->shaderprogram->ApplyTransformation(transformation->GetTransformationMatrix());
}

void DrawableObject::DrawObject() {
	this->shaderprogram->ApplyTransformation(transformation->GetTransformationMatrix());
	//this->shaderprogram->ApplyProjection();
	//this->shaderprogram->ApplyView();
	this->shaderprogram->UseShader();
	this->model->DrawModel();
	//this->shaderprogram->DeleteShader();
};
void DrawableObject::ScaleObject(float s) {
	//this->transformation->Scale(s);
}
void DrawableObject::MoveObject(float x, float y, float z){
	//this->transformation->Translate(x,y,z);
}

void DrawableObject::SpinObject(float x, float y, float z) {
	//this->transformation->Rotate(x,y,z);
}