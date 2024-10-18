#include "TransformationBuilder.h"

TransformationBuilder::TransformationBuilder() {
    composite = new TransformationComposite();
}

TransformationBuilder& TransformationBuilder::COMPONENT(TransformationComposite* component) {
    composite->AddTransformation(component);
    return *this;
}

TransformationBuilder& TransformationBuilder::ROTATE(float x, float y, float z, bool Repeat) {
    composite->AddTransformation(new TransformationRotate(x, y, z, Repeat));
    return *this;
}

TransformationBuilder& TransformationBuilder::SCALE(float scale) {
    composite->AddTransformation(new TransformationScale(scale));
    return *this;
}

TransformationBuilder& TransformationBuilder::TRANSLATE(float x, float y, float z) {
    composite->AddTransformation(new TransformationTranslate(x, y, z));
    return *this;
}

TransformationComposite* TransformationBuilder::Build() {
    return composite;
}

void TransformationBuilder::Reset() {
    delete composite;  
    composite = new TransformationComposite(); 
}