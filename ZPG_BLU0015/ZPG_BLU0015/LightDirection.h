#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Light.h"

class DirectionLight : public Light {
public:
	DirectionLight();
	DirectionLight(glm::vec3 AColor);
	DirectionLight(glm::vec3 AColor, glm::vec3 ADirection);
};