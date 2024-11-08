#include "Material.h"

Material::Material() {}

Material::Material(glm::vec3 AObjectColor, glm::vec3 AAmbientColor, float AShininess) {
	this->ObjectColor = AObjectColor;
	this->AmbientColor = AAmbientColor;
	this->Shininess = AShininess;
}

glm::vec3 Material::GetObjectColor() {
	return this->ObjectColor;
}

glm::vec3 Material::GetAmbientColor() {
	return this->AmbientColor;
}

float Material::GetShininess() {
	return this->Shininess;
}