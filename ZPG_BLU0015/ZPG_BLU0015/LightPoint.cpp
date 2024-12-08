/* Vratislav Blunar - BLU0015 */
#include "LightPoint.h"

PointLight::PointLight() :Light(){
	this->LightType = POINT;
}
PointLight::PointLight(glm::vec3 AColor):Light(AColor) {
	this->LightType = POINT;
}
PointLight::PointLight(glm::vec3 AColor, float AStrength) :Light(AColor, AStrength){
	this->LightType = POINT;
}