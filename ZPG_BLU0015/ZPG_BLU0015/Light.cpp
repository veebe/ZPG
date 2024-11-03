#include "Light.h"

Light::Light(glm::vec3 APosition, glm::vec3 AColor) {
	this->Position = APosition;
	this->Color = AColor;

	Notify(LIGHTPOS);
	Notify(LIGHTCOLOR);
}

Light::Light(glm::vec3 AColor) {
	this->Color = AColor;
	this->Position = glm::vec3(0, 0, 0);
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

void Light::Notify(NotifyType Atype) {
	for (auto observer : observers) {
		observer->OnUpdate(Atype);
	}
}