#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Transformation.h"

class TransformationTranslate : public Transformation {
public:
	TransformationTranslate(float x, float y, float z, bool ARepeat = false);

	void AddTranslation(float x, float y, float z);

	glm::mat4 GetTransformationMatrix() override;
	Transformation* Clone() const override;
private:
	glm::mat4 M;
	bool Repeat;
	glm::vec3 Place;
};