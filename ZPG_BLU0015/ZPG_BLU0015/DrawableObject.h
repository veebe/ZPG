#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"
#include "TransformationComposite.h"
#include "TransformationRotate.h"
#include "TransformationScale.h"
#include "TransformationTranslate.h"
#include "Camera.h"

class DrawableObject {
public:
	virtual ~DrawableObject() {};
	DrawableObject(TransformationComposite* ATransformation);

	virtual void DrawObject() = 0;
	virtual void ApplyLight(Light* ALight) = 0;
	virtual void ApplyCamera(Camera* ACamera) = 0;
	virtual void ClearLights() = 0;

	void SetNewTransformation(TransformationComposite* ATC);
protected:
	TransformationComposite* transformation;
};