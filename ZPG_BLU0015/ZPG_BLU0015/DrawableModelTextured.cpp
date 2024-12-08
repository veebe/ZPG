/* Vratislav Blunar - BLU0015 */
#include "DrawableModelTextured.h"

DrawableModelTextured::DrawableModelTextured(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation, Material* AMaterial, Texture* ATexture)
	:DrawableModel(Amodel, ASP, ATransformation, AMaterial)
{
	this->texture = ATexture;
}

void DrawableModelTextured::ShowSkyCube(bool AShowSkyCube) {
	this->shaderprogram->ShowSkyCube(AShowSkyCube);
}

void DrawableModelTextured::DrawObject() {
	this->shaderprogram->UseShader();
	this->shaderprogram->ApplyMaterial(this->material);
	this->shaderprogram->ApplyTransformation(this->transformation->GetTransformationMatrix());
	this->shaderprogram->ApplyTexture(this->texture);
	this->model->DrawModel();
	this->shaderprogram->UnUseShader();
}