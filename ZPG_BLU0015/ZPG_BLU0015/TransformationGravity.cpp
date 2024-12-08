/* Vratislav Blunar - BLU0015 */
#include "TransformationGravity.h"
#include "Application.h"

TransformationGravity::TransformationGravity(float x, float y, float z, float AAcceleration, float Abounce) {
    this->place = glm::vec3(x, y, z);
    this->acceleration = AAcceleration;
    this->bounce = Abounce;
}

glm::mat4 TransformationGravity::GetTransformationMatrix() {
    CalculateGravity();

    return M;
}

Transformation* TransformationGravity::Clone() const {
    return new TransformationGravity(*this);
}

void TransformationGravity::CalculateGravity() {
    double dtime = Application::getInstance().GetDeltaTime();
    dtime *= (dtime * acceleration);
    velocity += g * dtime;

    place += glm::vec3( 0, -velocity, 0);

    if (place.y <= 0.0f) {
        place.y = 0.0f; 
        velocity = velocity * - float(bounce / 100);
    }

    M = glm::translate(glm::mat4(1.0f), place);
}