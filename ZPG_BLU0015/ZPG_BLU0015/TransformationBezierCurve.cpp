/* Vratislav Blunar - BLU0015 */
#include "TransformationBezierCurve.h"

#include "Application.h"

TransformationBezierCurve::TransformationBezierCurve(glm::vec3 AStart, glm::vec3 AEnd, std::vector<glm::vec3> AControlPoints) {
    this->startPoint = AStart;
    this->endPoint = AEnd;
    this->controlPoints = AControlPoints;
}

glm::mat4 TransformationBezierCurve::GetTransformationMatrix() {
    CalculateBezier();

    return M;
}

Transformation* TransformationBezierCurve::Clone() const {
    return new TransformationBezierCurve(*this);
}

float Bernstein(int i, int n, float t) {
    float binomialCoeff = tgamma(n + 1) / (tgamma(i + 1) * tgamma(n - i + 1));
    return binomialCoeff * pow(1 - t, n - i) * pow(t, i);
}

void TransformationBezierCurve::CalculateBezier() {
    float deltaTime = Application::getInstance().GetDeltaTime();
    if (direction)
        t += deltaTime / duration;
    else
        t -= deltaTime / duration;

    if (t > 1.0f || t < 0.0f)
        direction = !direction;

    std::vector<glm::vec3> points = { startPoint };
    points.insert(points.end(), controlPoints.begin(), controlPoints.end());
    points.push_back(endPoint);

    glm::vec3 position = glm::vec3(0.0f);
    int n = points.size() - 1;

    for (int i = 0; i <= n; ++i) {
        position += Bernstein(i, n, t) * points[i];
    }

    M = glm::translate(glm::mat4(1.0f), position);
}