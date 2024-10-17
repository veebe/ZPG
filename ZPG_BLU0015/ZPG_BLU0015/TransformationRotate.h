#pragma once
#include "Transformation.h"

class TransformationRotate : public Transformation {
public:
	TransformationRotate(float x, float y, float z);

	glm::mat4 GetTransformationMatrix() override;
	Transformation* Clone() const override;
private:
	glm::mat4 M;
};