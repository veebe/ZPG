/* Vratislav Blunar - BLU0015 */
#include "TransformationTranslate.h"

TransformationTranslate::TransformationTranslate(float x, float y, float z, bool ARepeat) {
    M = glm::mat4(1.0f);
    AddTranslation(x, y, z);

    this->Repeat = ARepeat;
    this->Place = glm::vec3(x, y, z);
}

glm::mat4 TransformationTranslate::GetTransformationMatrix() {
    if (this->Repeat)
        AddTranslation(Place[0], Place[1], Place[2]);
    return M;
}

Transformation* TransformationTranslate::Clone() const{
	return new TransformationTranslate(*this);
}

void TransformationTranslate::AddTranslation(float x, float y, float z) {
    M = glm::translate(M, glm::vec3(x, y, z));
}