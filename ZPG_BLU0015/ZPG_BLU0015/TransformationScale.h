#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Transformation.h"

class TransformationScale : public Transformation {
public:
	TransformationScale(float scale);

	glm::mat4 GetTransformationMatrix() override;
	Transformation* Clone() const override;
private:
	glm::mat4 M;
};