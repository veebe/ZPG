#pragma once

#include "Model.h"
#include "vector"

class ModelSkyCube : public Model {
public:
	ModelSkyCube(std::vector<float> AModel);
	void DrawModel() override;
private:
	void BindVAO(GLuint AVBO) override;

};