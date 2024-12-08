#pragma once
/* Vratislav Blunar - BLU0015 */
#include "DrawableObject.h"

class DrawableLight : public DrawableObject {
public:	
	DrawableLight(Light* ALight, TransformationComposite* ATransformation);

	void DrawObject() override;
	void ApplyLight(Light* ALight) override;
	void ApplyCamera(Camera* ACamera) override;
	void ClearLights() override;
private:
	Light* light;
};