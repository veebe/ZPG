#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vector"

#include "observer.h"

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

enum NotifyType {
    VIEWMATRIX,
    PROJECTIONMATRIX
};


class Camera{
public:
    Camera();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    void MoveCameraWithMouse(double x, double y);
    void MoveCameraWithArrows(Direction Adirection, float ADeltaTime);
    
    void RegisterObserver(Observer* Aobserver);
    void RemoveObserver(Observer* Aobserver);
private:

    void NotifyObservers(NotifyType Atype); 
    std::vector<Observer*> observers;

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