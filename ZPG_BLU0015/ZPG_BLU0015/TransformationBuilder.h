#pragma once
#include "TransformationComposite.h"
#include "TransformationRotate.h"
#include "TransformationTranslate.h"
#include "TransformationScale.h"
#include <glm/gtc/matrix_transform.hpp>

class TransformationBuilder {
public:
    TransformationBuilder();

    TransformationBuilder& COMPONENT(TransformationComposite* component);
    TransformationBuilder& ROTATE(float x, float y, float z, bool Repeat = false);
    TransformationBuilder& SCALE(float scale);
    TransformationBuilder& TRANSLATE(float x, float y, float z);

    TransformationComposite* Build();
    void Reset();

private:
    TransformationComposite* composite;
};