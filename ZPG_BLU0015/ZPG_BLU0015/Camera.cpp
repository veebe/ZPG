#include "Camera.h"

Camera::Camera() {
	this->eye = glm::vec3(0.0f, 0.0f, 10.0f);
	this->target = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->yaw = -90.0f;
	this->pitch = 0.0f;
}

glm::mat4 Camera::GetProjectionMatrix() {
	return glm::perspective(glm::radians(60.f), 4.0f / 3.0f, 0.1f, 100.0f);
	
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(eye, eye + target, up);
}

void Camera::MoveCameraWithMouse(double x, double y) {

	if (this->firstMouse)
	{
		this->lastX = x;
		this->lastY = y;
		this->firstMouse = false;
	}
	float xoffset = x - this->lastX;
	float yoffset = this->lastY - y;
	this->lastX = x;
	this->lastY = y;

	float sensitivity;
	if (abs(xoffset) < 1.5)
		sensitivity = 0.05f;
	else if (abs(xoffset) < 3)
		sensitivity = 0.1f;
	else if(abs(xoffset) < 6)
		sensitivity = 0.2f;
	else
		sensitivity = 0.4f;
	
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	this->yaw += xoffset;
	this->pitch += yoffset;

	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	float yaw_rad = glm::radians(this->yaw);
	float pitch_rad = glm::radians(this->pitch);

	glm::vec3 ltarget;
	ltarget.x = cos(yaw_rad) * cos(pitch_rad);
	ltarget.y = sin(pitch_rad);
	ltarget.z = sin(yaw_rad) * cos(pitch_rad);
	this->target = glm::normalize(ltarget);

	Notify(VIEWMATRIX);
}

void Camera::MoveCameraWithArrows(Direction Adirection, float ADeltaTime) {
	switch (Adirection) {
	case FORWARD:
		this->eye += this->target * (this->speed * ADeltaTime);
		break;
	case BACKWARD:
		this->eye -= this->target * (this->speed * ADeltaTime);
		break;
	case LEFT:
		this->eye -= glm::normalize(glm::cross(this->target, this->up)) * (this->speed * ADeltaTime);
		break;
	case RIGHT:
		this->eye += glm::normalize(glm::cross(this->target, this->up)) * (this->speed * ADeltaTime);
		break;
	case UP:
		this->eye += this->up * (this->speed * ADeltaTime);
		break;
	case DOWN:
		this->eye -= this->up * (this->speed * ADeltaTime);
		break;
	default:
		break;
	}
	Notify(VIEWMATRIX);
}

void Camera::Attach(IObserver* Aobserver) {
	observers.push_back(Aobserver);
}

void Camera::Detach(IObserver* Aobserver) {
	observers.erase(std::remove(observers.begin(), observers.end(), Aobserver), observers.end());
}

void Camera::Notify(NotifyType Atype) {
	switch (Atype) {
	case VIEWMATRIX:
		for (auto observer : observers) {
			observer->OnCameraChangedView();
		}
		break;
	case PROJECTIONMATRIX:
		for (auto observer : observers) {
			observer->OnCameraChangedProjection();
		}
		break;
	default:
		break;
	}
}