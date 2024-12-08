/* Vratislav Blunar - BLU0015 */
#include "TransformationComposite.h"

void TransformationComposite::AddTransformation(Transformation* transformation) {
    transformations.push_back(transformation);
}

glm::mat4 TransformationComposite::GetTransformationMatrix() {
    glm::mat4 result = glm::mat4(1.0f);
    for (auto& transformation : transformations) {
        result *= transformation->GetTransformationMatrix();
    }
    return result;
}

TransformationComposite::~TransformationComposite() {
    for (auto& transformation : transformations) {
        delete transformation;
    }
}

Transformation* TransformationComposite::Clone() const {
    TransformationComposite* clone = new TransformationComposite();
    for (auto& transformation : transformations) {
        clone->AddTransformation(transformation->Clone()); 
    }
    return clone;
}

Transformation* TransformationComposite::GetSingleTransformationMatrix(int AIndex) {
    return transformations[AIndex];
}