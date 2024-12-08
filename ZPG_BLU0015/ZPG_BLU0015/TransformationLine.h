#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Transformation.h"

class TransformationLine : public Transformation {
public:
	TransformationLine(glm::vec3 AP0, glm::vec3 AP1);

	glm::mat4 GetTransformationMatrix() override;
	Transformation* Clone() const override;

private:
	void CalculateLine();

	glm::vec3 P0, P1;
	glm::mat4 M = glm::mat4(1.f);

	float duration = 3;
	float t = 0;
	bool direction = true;
};