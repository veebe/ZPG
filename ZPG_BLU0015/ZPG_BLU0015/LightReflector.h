#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Light.h"
#include "Camera.h"

class ReflectorLight : public Light, IObserver {
public:
	ReflectorLight();
	ReflectorLight(glm::vec3 AColor);
	ReflectorLight(glm::vec3 AColor, float AStrength);

	void AddCamera(Camera* ACamera);
	void OnCameraChangePosition();
	void OnUpdate(NotifyType ANotifyType);

private:
	Camera* camera;
};