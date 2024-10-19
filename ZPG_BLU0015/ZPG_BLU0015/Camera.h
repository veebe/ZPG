#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vector"

#include "IObserver.h"
#include "ISubject.h"

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera : ISubject {
public:
    Camera();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    void MoveCameraWithMouse(double x, double y);
    void MoveCameraWithArrows(Direction Adirection, float ADeltaTime);
    
    void Attach(IObserver* Aobserver) override;
    void Detach(IObserver* Aobserver) override;
private:

    void Notify(NotifyType Atype) override; 
    std::vector<IObserver*> observers;

    glm::vec3 target;
    glm::vec3 up;
    glm::vec3 eye;

    float speed = 15.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;
    bool firstMouse = true;
    float lastX = 0.0f;
    float lastY = 0.0f;

};