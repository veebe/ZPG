#include "DrawableObject.h"

DrawableObject::DrawableObject(Model* Amodel, ShaderProgram* ASP, Transformation* ATransformation) {
	this->model = Amodel;
	this->shaderprogram = ASP;
	this->transformation = ATransformation;
};
void DrawableObject::DrawObject() {
	this->shaderprogram->ApplyTransformation(transformation->GetTransformationMatrix());
	this->shaderprogram->ApplyProjection(glm::perspective(glm::radians(90.0f), (float)4 / (float)3, 0.1f, 100.0f));
	this->shaderprogram->ApplyView(glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	this->shaderprogram->UseShader();
	this->model->DrawModel();
	//this->shaderprogram->DeleteShader();
};
void DrawableObject::ScaleObject(float s) {
	this->transformation->Scale(s);
}
void DrawableObject::MoveObject(float x, float y, float z){
	this->transformation->Translate(x,y,z);
}

void DrawableObject::SpinObject(float x, float y, float z) {
	this->transformation->Rotate(x,y,z);
}