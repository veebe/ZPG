/* Vratislav Blunar - BLU0015 */
#include "TransformationBezier.h"
#include "Application.h"

TransformationBezier::TransformationBezier(glm::vec3 AP0, glm::vec3 AP1, glm::vec3 AP2, glm::vec3 AP3) {
	this->P0 = AP0;
	this->P1 = AP1;
	this->P2 = AP2;
	this->P3 = AP3;
}

glm::mat4 TransformationBezier::GetTransformationMatrix() {
    CalculateBezier();

    return M;
}

Transformation* TransformationBezier::Clone() const {
    return new TransformationBezier(*this);
}

void TransformationBezier::CalculateBezier() {
    float deltaTime = Application::getInstance().GetDeltaTime();
    if (direction)
        t += deltaTime / duration; 
    else
        t -= deltaTime / duration;
    
    if (t > 1.0f || t < 0.0f)
        direction = !direction;

    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    glm::vec3 result = uuu * P0;          
    result += 3.0f * uu * t * P1;         
    result += 3.0f * u * tt * P2;         
    result += ttt * P3;                  

    M = glm::translate(glm::mat4(1.0f), result);
}