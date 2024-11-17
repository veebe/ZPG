#include "LightReflector.h"

ReflectorLight::ReflectorLight() 
			   :Light(){
	this->LightType = REFLECTOR;
	this->camera = nullptr;
}

ReflectorLight::ReflectorLight(glm::vec3 AColor) 
			   :Light(AColor) {
	this->LightType = REFLECTOR;
	this->camera = nullptr;
}

ReflectorLight::ReflectorLight(glm::vec3 AColor, float AStrength)
			   :Light(AColor, AStrength) {
	this->LightType = REFLECTOR;
	this->camera = nullptr;
}

void ReflectorLight::AddCamera(Camera* ACamera) {
	if (this->camera != ACamera) {
		ACamera->Attach(this);
		camera = ACamera;
	}
}

void ReflectorLight::OnCameraChangePosition() {
	SetLightPostion(camera->GetCameraPosition());
}

void ReflectorLight::OnUpdate(NotifyType ANotifyType) {
	switch (ANotifyType) {
	case VIEWMATRIX:
		OnCameraChangePosition();
		break;
	case PROJECTIONMATRIX:
		OnCameraChangePosition();
		break;
	default:
		break;
	}
}