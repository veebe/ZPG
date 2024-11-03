#include "DrawableLight.h"

DrawableLight::DrawableLight(Light* ALight, TransformationComposite* ATransformation) 
			  :DrawableObject(ATransformation), light(ALight) {}

void DrawableLight::DrawObject() {
	this->light->SetLightPostion(glm::vec3(this->transformation->GetTransformationMatrix()[3]));
}

void DrawableLight::ApplyLight(Light* ALight) {};
void DrawableLight::ApplyCamera(Camera* ACamera) {};