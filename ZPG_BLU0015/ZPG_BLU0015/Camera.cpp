/* Vratislav Blunar - BLU0015 */
#include "Camera.h"

Camera::Camera() {
	this->eye = glm::vec3(0.0f, 1.0f, 10.0f);
	this->target = glm::vec3(0.0f, 0.0f, -1.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);

	this->yaw = -90.0f;
	this->pitch = 0.0f;
}

glm::mat4 Camera::GetProjectionMatrix() {
	return glm::perspective(glm::radians(60.f), float(Width / Height), 0.1f, 300.0f);
}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(eye, eye + target, up);
}

glm::vec3 Camera::GetCameraPosition() {
	return glm::vec3( this->eye.x, this->eye.y, this->eye.z);
}

glm::vec3 Camera::GetCameraDirection() {
	return this->target;
}

void Camera::ResizeWindow(int w, int h) {
	this->Width = w;
	this->Height = h;
	Notify(PROJECTIONMATRIX);
}

glm::vec3 Camera::CalculateClickedPos(glm::vec3 AscreenX) {
	glm::vec4 viewPort = glm::vec4(0, 0, Width, Height);
	return glm::unProject(AscreenX, GetViewMatrix(), GetProjectionMatrix(), viewPort);
}

void Camera::MoveCameraWithMouse(double xoffset, double yoffset) {

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

void Camera::Notify(NotifyType Atype) {
	for (auto observer : observers) {
		observer->OnUpdate(Atype);
	}
}