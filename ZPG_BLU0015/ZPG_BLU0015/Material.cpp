#include "Material.h"

Material::Material() {}

Material::Material(glm::vec3 AObjectColor, glm::vec3 AAmbientColor, float AShininess) {
	this->ObjectColor = AObjectColor;
	this->AmbientColor = AAmbientColor;
	this->Shininess = AShininess;
	
	Notify(MATERIAL); // notify somewhere else
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

void Material::Attach(IObserver* Aobserver) {
	observers.push_back(Aobserver);
}

void Material::Detach(IObserver* Aobserver) {
	observers.erase(std::remove(observers.begin(), observers.end(), Aobserver), observers.end());
}

void Material::Notify(NotifyType Atype) {
	for (auto observer : observers) {
		observer->OnUpdate(MATERIAL);
	}
}