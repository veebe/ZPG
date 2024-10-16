#include "Transformation.h"

Transformation::Transformation() {
	M = glm::mat4(1.0f);
}

void Transformation::Rotate(float x, float y, float z) {
	M = glm::rotate(M, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	M = glm::rotate(M, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(M, glm::radians(z), glm::vec3(0.f, 0.0f, 1.0f));
}

void Transformation::Scale(float scale) {
	M = glm::scale(M, glm::vec3(scale));
}

void Transformation::Translate(float x, float y, float z) {
	M = glm::translate(M, glm::vec3(x, y, z));
}

glm::mat4 Transformation::GetTransformationMatrix() {
	return M;
}