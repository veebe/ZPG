#include "Light.h"

Light::Light(glm::vec3 APosition, glm::vec3 AColor) {
	this->Position = APosition;
	this->Color = AColor;

	Notify(LIGHTPOS);
	Notify(LIGHTCOLOR);
}
glm::vec3 Light::GetLightPosition() {
	return this->Position;
}
glm::vec3 Light::GetLightColor() {
	return this->Color;
}

void Light::Attach(IObserver* Aobserver) {
	observers.push_back(Aobserver);
}

void Light::Detach(IObserver* Aobserver) {
	observers.erase(std::remove(observers.begin(), observers.end(), Aobserver), observers.end());
}

void Light::Notify(NotifyType Atype) {
	switch (Atype) {
	case LIGHTPOS:
		for (auto observer : observers) {
			observer->OnLightChangePosition();
		}
		break;
	case LIGHTCOLOR:
		for (auto observer : observers) {
			observer->OnLightChangeColor();
		}
		break;
	default:
		break;
	}
}