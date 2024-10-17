#include "TransformationRotate.h"

TransformationRotate::TransformationRotate(float x, float y, float z) {
    M = glm::mat4(1.0f);
    M = glm::rotate(M, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
    M = glm::rotate(M, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
    M = glm::rotate(M, glm::radians(z), glm::vec3(0.f, 0.0f, 1.0f));
}

glm::mat4 TransformationRotate::GetTransformationMatrix() {
    return M;
}

Transformation* TransformationRotate::Clone() const {
    return new TransformationRotate(*this);
}