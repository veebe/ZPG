#include "TransformationScale.h"

TransformationScale::TransformationScale(float scale) {
    M = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
}

glm::mat4 TransformationScale::GetTransformationMatrix() {
    return M;
}

Transformation* TransformationScale::Clone() const {
    return new TransformationScale(*this);
}