#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Transformation.h"

class TransformationBezier : public Transformation {
public:
	TransformationBezier(glm::vec3 AP0, glm::vec3 AP1, glm::vec3 AP2, glm::vec3 AP3);

	glm::mat4 GetTransformationMatrix() override;
	Transformation* Clone() const override;

private:
	void CalculateBezier();

	glm::vec3 P0, P1, P2, P3;
	glm::mat4 M = glm::mat4(1.f);

	float duration = 10;
	float t = 0;
	bool direction = true;
};