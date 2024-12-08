#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Light.h"

class PointLight : public Light {
public:
	PointLight();
	PointLight(glm::vec3 AColor);
	PointLight(glm::vec3 AColor, float AStrength);
};