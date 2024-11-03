#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vector"

#include "ISubject.h"

class Material : ISubject {
public:
	Material();
	Material(glm::vec3 AObjectColor, glm::vec3 AAmbientColor, float AShininess);

	glm::vec3 GetObjectColor();
	glm::vec3 GetAmbientColor();
	float GetShininess();

	void Attach(IObserver* Aobserver) override;
	void Detach(IObserver* Aobserver) override;
private:
	glm::vec3 ObjectColor = glm::vec3(0.38f, 0.65f, 0.81f);
	glm::vec3 AmbientColor = glm::vec3(0.1f,0.1f,0.1f);
	float Shininess = 32;

	void Notify(NotifyType Atype) override;
	std::vector<IObserver*> observers;
};