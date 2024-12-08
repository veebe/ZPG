#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Model.h"
#include "../../Models/suzi_smooth.h"

class ModelSuzi : public Model {
public:
	ModelSuzi();
	void DrawModel() override;
};