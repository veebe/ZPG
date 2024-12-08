/* Vratislav Blunar - BLU0015 */
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

TransformationBuilder& TransformationBuilder::TRANSLATE(glm::vec3 P, bool Repeat) {
    composite->AddTransformation(new TransformationTranslate(P.x, P.y, P.z, Repeat));
    return *this;
}

TransformationComposite* TransformationBuilder::Build() {
    TransformationComposite* result = static_cast<TransformationComposite*>(composite->Clone());
    composite = new TransformationComposite();
    return result;
}

TransformationBuilder& TransformationBuilder::GRAVITY(float x, float y, float z, float AAcceleration, float ABounce) {
    composite->AddTransformation(new TransformationGravity(x, y, z, AAcceleration, ABounce));
    return *this;
}

TransformationBuilder& TransformationBuilder::BEZIER(glm::vec3 P0, glm::vec3 P1, glm::vec3 P2, glm::vec3 P3) {
    composite->AddTransformation(new TransformationBezier(P0, P1, P2, P3));
    return *this;
}

TransformationBuilder& TransformationBuilder::BEZIER(glm::vec3 P0, glm::vec3 P1, std::vector<glm::vec3> APoints) {
    composite->AddTransformation(new TransformationBezierCurve(P0, P1, APoints));
    return *this;
}

TransformationBuilder& TransformationBuilder::LINE(glm::vec3 P0, glm::vec3 P1) {
    composite->AddTransformation(new TransformationLine(P0, P1));
    return *this;
}