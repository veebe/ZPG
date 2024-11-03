#pragma once
#include "glm/glm.hpp"
#include "ISubject.h"
#include "IObserver.h"
#include "vector"

class Light : public ISubject {
public:
	Light(glm::vec3 APosition, glm::vec3 AColor);
	Light(glm::vec3 AColor);

	glm::vec3 GetLightPosition();
	glm::vec3 GetLightColor();

	void SetLightPostion(glm::vec3 APosition);
	void SetLightColor(glm::vec3 AColor);

private:
	void Notify(NotifyType Atype) override;

	glm::vec3 Position;
	glm::vec3 Color;
};