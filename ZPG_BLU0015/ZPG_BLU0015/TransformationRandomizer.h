#pragma once
/* Vratislav Blunar - BLU0015 */
#include "TransformationComposite.h"
#include "TransformationRotate.h"
#include "TransformationTranslate.h"
#include "TransformationScale.h"
#include <random>

class TransformationRandomizer {
public:
    static TransformationComposite* CreateRandomTransformation();
    static TransformationComposite* CreateRandomTransformationStars();
    static TransformationComposite* CreateRandomTransformationGrass();

    static float RandomFloat(float min, float max);
};