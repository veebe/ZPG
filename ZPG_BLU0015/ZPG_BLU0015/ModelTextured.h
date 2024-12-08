#pragma once
/* Vratislav Blunar - BLU0015 */
#include "Model.h"
#include "vector"
#include "Texture.h"

class ModelTextured : public Model {
public:
	ModelTextured(std::vector<float> AModel);
	void DrawModel() override;
private:
	void BindVAO(GLuint AVBO) override;

};