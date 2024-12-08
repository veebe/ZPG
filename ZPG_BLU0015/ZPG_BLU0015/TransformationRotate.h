#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Transformation.h"

class TransformationRotate : public Transformation {
public:
	TransformationRotate(float x, float y, float z, bool ARepeat = false);

	glm::mat4 GetTransformationMatrix() override;

	void AddRotation(float x, float y, float z);
	Transformation* Clone() const override;
private:
	glm::mat4 M;
	bool Repeat;
	glm::vec3 Angle;
};