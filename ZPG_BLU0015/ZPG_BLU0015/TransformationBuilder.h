#pragma once
#include "TransformationComposite.h"
#include "TransformationRotate.h"
#include "TransformationTranslate.h"
#include "TransformationScale.h"
#include "TransformationGravity.h"

class TransformationBuilder {
public:
    TransformationBuilder();

    TransformationBuilder& COMPONENT(TransformationComposite* component);
    TransformationBuilder& ROTATE(float x, float y, float z, bool Repeat = false);
    TransformationBuilder& SCALE(float scale);
    TransformationBuilder& TRANSLATE(float x, float y, float z, bool Repeat = false);
    TransformationBuilder& GRAVITY(float x, float y, float z, float AAcceleration = 3, float ABounce = 93);

    TransformationComposite* Build();

private:
    TransformationComposite* composite;
};