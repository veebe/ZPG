#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Transformation.h"
#include "TransformationGravity.h"

class TransformationComposite : public Transformation {
public:
    void AddTransformation(Transformation* transformation);
    glm::mat4 GetTransformationMatrix() override;
    Transformation* GetSingleTransformationMatrix(int AIndex);

    ~TransformationComposite();
    Transformation* Clone() const override;
private:
    std::vector<Transformation*> transformations;
};