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

TransformationBuilder& TransformationBuilder::TRANSLATE(float x, float y, float z, bool Repeat) {
    composite->AddTransformation(new TransformationTranslate(x, y, z, Repeat));
    return *this;
}

TransformationComposite* TransformationBuilder::Build() {
    TransformationComposite* result = static_cast<TransformationComposite*>(composite->Clone());
    composite = new TransformationComposite();
    return result;
}