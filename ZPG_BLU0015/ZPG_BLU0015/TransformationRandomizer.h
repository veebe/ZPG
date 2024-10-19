#pragma once
#include "TransformationComposite.h"
#include "TransformationRotate.h"
#include "TransformationTranslate.h"
#include "TransformationScale.h"
#include <random>

class TransformationRandomizer {
public:
    static TransformationComposite* CreateRandomTransformation();

    static float RandomFloat(float min, float max);
};