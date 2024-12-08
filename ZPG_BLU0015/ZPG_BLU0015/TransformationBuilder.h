#pragma once
/* Vratislav Blunar - BLU0015 */
#include "TransformationComposite.h"
#include "TransformationRotate.h"
#include "TransformationTranslate.h"
#include "TransformationScale.h"
#include "TransformationGravity.h"
#include "TransformationBezier.h"
#include "TransformationBezierCurve.h"
#include "TransformationLine.h"

class TransformationBuilder {
public:
    TransformationBuilder();

    TransformationBuilder& COMPONENT(TransformationComposite* component);
    TransformationBuilder& ROTATE(float x, float y, float z, bool Repeat = false);
    TransformationBuilder& SCALE(float scale);
    TransformationBuilder& TRANSLATE(float x, float y, float z, bool Repeat = false);
    TransformationBuilder& TRANSLATE(glm::vec3 P, bool Repeat = false);
    TransformationBuilder& GRAVITY(float x, float y, float z, float AAcceleration = 3, float ABounce = 93);
    TransformationBuilder& BEZIER(glm::vec3 P0, glm::vec3 P1, glm::vec3 P2, glm::vec3 P3 );
    TransformationBuilder& BEZIER(glm::vec3 P0, glm::vec3 P1, std::vector<glm::vec3> APoints);
    TransformationBuilder& LINE(glm::vec3 P0, glm::vec3 P1);

    TransformationComposite* Build();

private:
    TransformationComposite* composite;
};