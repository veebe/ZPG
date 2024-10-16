#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


class Camera
{
public:
    Camera();

    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
};