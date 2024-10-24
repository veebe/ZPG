#pragma once
#include "glm/glm.hpp"
#include "ISubject.h"
#include "IObserver.h"
#include "vector"

class Light : ISubject {
public:
	Light(glm::vec3 APosition, glm::vec3 AColor);
	glm::vec3 GetLightPosition();
	glm::vec3 GetLightColor();

	void Attach(IObserver* Aobserver) override;
	void Detach(IObserver* Aobserver) override;

private:
	void Notify(NotifyType Atype) override;

	glm::vec3 Position;
	glm::vec3 Color;
	std::vector<IObserver*> observers;
};