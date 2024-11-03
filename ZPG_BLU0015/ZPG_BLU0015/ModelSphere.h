#pragma once
#include "Model.h"
#include "../../Models/sphere.h"

class ModelSphere : public Model {
public:
	ModelSphere();
	void DrawModel() override;
};