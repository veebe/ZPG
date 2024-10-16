#include "Camera.h"

Camera::Camera() {

}

glm::mat4 Camera::GetProjectionMatrix() {
	return glm::perspective(glm::radians(90.0f), (float)4 / (float)3, 0.1f, 100.0f);
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}