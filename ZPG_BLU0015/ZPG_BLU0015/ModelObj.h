#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Model.h"
#include "ModelLoader.h"

class ModelObj : public Model, ModelLoader {
public:
	ModelObj(std::string AModelFile);

	void DrawModel() override;
};