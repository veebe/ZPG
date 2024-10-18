#include "TransformationRotate.h"

TransformationRotate::TransformationRotate(float x, float y, float z, bool ARepeat)  {
    M = glm::mat4(1.0f);
    AddRotation(x, y, z);
    
    this->Repeat = ARepeat;
    this->Angle = glm::vec3(x,y,z);
}

glm::mat4 TransformationRotate::GetTransformationMatrix() {
    if (this->Repeat)
        AddRotation(Angle[0], Angle[1], Angle[2]);
    return M;
}

Transformation* TransformationRotate::Clone() const {
    return new TransformationRotate(*this);
}

void TransformationRotate::AddRotation(float x, float y, float z) {
    M = glm::rotate(M, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
    M = glm::rotate(M, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
    M = glm::rotate(M, glm::radians(z), glm::vec3(0.f, 0.0f, 1.0f));
}