/* Vratislav Blunar - BLU0015 */
#include "TransformationLine.h"

#include "TransformationBezier.h"
#include "Application.h"

TransformationLine::TransformationLine(glm::vec3 AP0, glm::vec3 AP1) {
    this->P0 = AP0;
    this->P1 = AP1;
}

glm::mat4 TransformationLine::GetTransformationMatrix() {
    CalculateLine();

    return M;
}

Transformation* TransformationLine::Clone() const {
    return new TransformationLine(*this);
}

void TransformationLine::CalculateLine() {
    float deltaTime = Application::getInstance().GetDeltaTime();
    if (direction)
        t += deltaTime / duration;
    else
        t -= deltaTime / duration;

    if (t > 1.0f || t < 0.0f)
        direction = !direction;


    glm::vec3 result;

    result = P0 + t * (P1 - P0);

    M = glm::translate(glm::mat4(1.0f), result);
}