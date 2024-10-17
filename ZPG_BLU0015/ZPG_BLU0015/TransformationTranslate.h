#pragma once
#include "Transformation.h"

class TransformationTranslate : public Transformation {
public:
	TransformationTranslate(float x, float y, float z);

	glm::mat4 GetTransformationMatrix() override;
	Transformation* Clone() const override;
private:
	glm::mat4 M;
};