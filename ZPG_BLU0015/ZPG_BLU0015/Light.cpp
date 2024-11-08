#include "Light.h"

Light::Light() {}

Light::Light(glm::vec3 AColor) {
	this->Color = AColor;
}

Light::Light(glm::vec3 AColor, float AStrength) {
	this->Color = AColor;
	this->Strength = AStrength;
}

Light::Light(float AStrength) {
	this->Strength = AStrength;
}

Light::Light(const Light& ACopy) {
	this->Position = ACopy.Position;
	this->Color = ACopy.Color;
	this->Strength = ACopy.Strength;
}

void Light::SetLightPostion(glm::vec3 APosition) {
	this->Position = APosition;
	Notify(LIGHTPOS);
}

void Light::SetLightColor(glm::vec3 AColor) {
	this->Color = AColor;
	Notify(LIGHTCOLOR);
}

glm::vec3 Light::GetLightPosition() {
	return this->Position;
}
glm::vec3 Light::GetLightColor() {
	return this->Color;
}

float Light::GetLightStrength() {
	return this->Strength;
}

void Light::Notify(NotifyType Atype) {
	for (auto observer : observers) {
		observer->OnUpdate(Atype);
	}
}