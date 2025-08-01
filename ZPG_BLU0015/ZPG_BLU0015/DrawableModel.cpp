/* Vratislav Blunar - BLU0015 */
#include "DrawableModel.h"
#include "ModelTextured.h"

DrawableModel::DrawableModel(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation, Material* AMaterial)
			  :DrawableObject(ATransformation), model(Amodel), shaderprogram(ASP), material(AMaterial) {};


DrawableModel::DrawableModel(const DrawableModel& ADrawableModel)
			:DrawableObject(ADrawableModel.transformation), model(ADrawableModel.model), shaderprogram(ADrawableModel.shaderprogram), material(ADrawableModel.material) {
}

DrawableModel* DrawableModel::clone() const {
	return new DrawableModel(*this);
}

void DrawableModel::DrawObject() {
	this->shaderprogram->UseShader();
	this->shaderprogram->ApplyMaterial(this->material);
	this->shaderprogram->ApplyTransformation(this->transformation->GetTransformationMatrix());
	this->model->DrawModel();
	this->shaderprogram->UnUseShader();
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