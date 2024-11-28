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
    float randomRotationX = RandomFloat(-7.f, 7.f);
    float randomRotationY = RandomFloat(0.f, 360.f);
    float randomRotationZ = RandomFloat(-7.f, 7.f);
    float randomTranslateX = 15;
    float randomTranslateZ = -15;
    while(randomTranslateX > -5 && randomTranslateX < 30 && randomTranslateZ > -35 && randomTranslateZ < 5){
        randomTranslateX = RandomFloat(-50.f, 50.f);
        randomTranslateZ = RandomFloat(-50.f, 50.f);
    }
    float randomTranslateY = 0;
        

    transformation->AddTransformation(new TransformationTranslate(randomTranslateX, randomTranslateY, randomTranslateZ));
    transformation->AddTransformation(new TransformationScale(randomScale));
    transformation->AddTransformation(new TransformationRotate(randomRotationX, randomRotationY, randomRotationZ));

    return transformation;
}

TransformationComposite* TransformationRandomizer::CreateRandomTransformationStars() {
    TransformationComposite* transformation = new TransformationComposite();

    float randomScale = RandomFloat(0.2, 0.5);

    float randomTranslateX = RandomFloat(-230.f, 230.f);
    float randomTranslateZ = RandomFloat(-230.f, 230.f);
    float randomTranslateY = RandomFloat( 200.f, 270.f);


    transformation->AddTransformation(new TransformationTranslate(randomTranslateX, randomTranslateY, randomTranslateZ));
    transformation->AddTransformation(new TransformationScale(randomScale));

    return transformation;
}