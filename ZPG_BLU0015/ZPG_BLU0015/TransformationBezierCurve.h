#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Transformation.h"

class TransformationBezierCurve : public Transformation {
public:
	TransformationBezierCurve(glm::vec3 AStart, glm::vec3 AEnd, std::vector<glm::vec3> AControlPoints);

	glm::mat4 GetTransformationMatrix() override;
	Transformation* Clone() const override;

private:
	void CalculateBezier();

	glm::vec3 startPoint;                   
	glm::vec3 endPoint;                     
	std::vector<glm::vec3> controlPoints;   

	glm::mat4 M = glm::mat4(1.f);

	float duration = 10;
	float t = 0;
	bool direction = true;
};