#pragma once
#include "Transformation.h"
#include "TransformationRotate.h"

class TransformationComposite : public Transformation {
private:
    std::vector<Transformation*> transformations;
public:
    void AddTransformation(Transformation* transformation);
    glm::mat4 GetTransformationMatrix() override;
    ~TransformationComposite();
    Transformation* Clone() const override;
};