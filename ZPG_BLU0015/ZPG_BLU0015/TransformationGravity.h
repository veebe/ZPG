#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Transformation.h"

class TransformationGravity : public Transformation {
public:
	TransformationGravity(float x, float y, float z, float AAcceleration = 3, float Abounce = 93);

	glm::mat4 GetTransformationMatrix() override;
	Transformation* Clone() const override;

private:
	void CalculateGravity();

	const float g = 9.81;
	glm::mat4 M = glm::mat4(1.f);
	glm::vec3 place = glm::vec3(0.f, 0.f, 0.f);;
	double velocity = 0;
	float acceleration = 3;
	float bounce = 93;
};