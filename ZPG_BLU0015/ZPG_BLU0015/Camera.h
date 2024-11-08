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

class Camera : public ISubject {
public:
    Camera();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    void MoveCameraWithMouse(double xoffset, double yoffset);
    void MoveCameraWithArrows(Direction Adirection, float ADeltaTime);

    void ResizeWindow(int w, int h);

    glm::vec3 GetCameraPosition();
private:

    void Notify(NotifyType Atype) override; 
    

    glm::vec3 target;
    glm::vec3 up;
    glm::vec3 eye;

    float speed = 15.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;

    int Width = 800;
    int Height = 600;

};