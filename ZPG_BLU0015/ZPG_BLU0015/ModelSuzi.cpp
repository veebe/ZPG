#include "ModelSuzi.h"

ModelSuzi::ModelSuzi() {


	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(suziSmooth), suziSmooth, GL_STATIC_DRAW);

	BindVAO(VBO);
};

void ModelSuzi::DrawModel() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 2904);
};