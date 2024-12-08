#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Model.h"
#include "../../Models/bushes.h"

class ModelBush : public Model {
public:
	ModelBush();
	void DrawModel() override;
};