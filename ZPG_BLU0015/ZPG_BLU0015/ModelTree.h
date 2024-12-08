#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Model.h"
#include "../../Models/tree.h"

class ModelTree : public Model {
public:
	ModelTree();
	void DrawModel() override;
};