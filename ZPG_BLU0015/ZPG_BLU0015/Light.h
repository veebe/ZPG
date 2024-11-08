#pragma once
#include "glm/glm.hpp"
#include "ISubject.h"
#include "IObserver.h"
#include "vector"

class Light : public ISubject {
public:
	Light();
	Light(glm::vec3 AColor);
	Light(glm::vec3 AColor, float AStrength);
	Light(float AStrength);
	Light(const Light& ACopy);
	

	glm::vec3 GetLightPosition();
	glm::vec3 GetLightColor();
	float GetLightStrength();

	void SetLightPostion(glm::vec3 APosition);
	void SetLightColor(glm::vec3 AColor);

private:
	void Notify(NotifyType Atype) override;

	glm::vec3 Position = glm::vec3(0.0, 10.0, 0.0);
	glm::vec3 Color = glm::vec3(1.0, 1.0, 1.0);
	float Strength = 30;
};