#include "TransformationRandomizer.h"

float TransformationRandomizer::RandomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return static_cast<float>(dis(gen));
}

TransformationComposite* TransformationRandomizer::CreateRandomTransformation() {
    TransformationComposite* transformation = new TransformationComposite();

    float randomScale =  RandomFloat(0.5f, 3.f);
    float randomRotationX = RandomFloat(-1.f, 1.f);
    float randomRotationY = RandomFloat(0.f, 360.f);
    float randomRotationZ = 0; //RandomFloat(-1.f, 1.f);
    float randomTranslateX = RandomFloat(-25.f, 25.f);
    float randomTranslateY = 0;
    float randomTranslateZ = RandomFloat(-25.f, 25.f);

    transformation->AddTransformation(new TransformationScale(randomScale));
    transformation->AddTransformation(new TransformationRotate(randomRotationX, randomRotationY, randomRotationZ));
    transformation->AddTransformation(new TransformationTranslate(randomTranslateX, randomTranslateY, randomTranslateZ));

    return transformation;
}
