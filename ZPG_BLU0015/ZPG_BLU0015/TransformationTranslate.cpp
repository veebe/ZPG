#include "TransformationTranslate.h"

TransformationTranslate::TransformationTranslate(float x, float y, float z) {
    M = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
}

glm::mat4 TransformationTranslate::GetTransformationMatrix() {
    return M;
}

Transformation* TransformationTranslate::Clone() const{
	return new TransformationTranslate(*this);
}