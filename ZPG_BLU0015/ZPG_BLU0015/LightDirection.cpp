#include "LightDirection.h"

DirectionLight::DirectionLight() : Light(){
	this->LightType = DIRECTION;
	this->Strength = 1000;
}
DirectionLight::DirectionLight(glm::vec3 AColor) : Light(AColor) {
	this->LightType = DIRECTION;
	this->Strength = 1000;
}
DirectionLight::DirectionLight(glm::vec3 AColor, glm::vec3 ADirection) : Light(AColor, -ADirection) {
	this->LightType = DIRECTION;
	this->Strength = 1000;
}