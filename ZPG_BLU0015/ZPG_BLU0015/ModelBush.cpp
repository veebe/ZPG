#include "ModelBush.h"

ModelBush::ModelBush() {

	
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bushes), bushes, GL_STATIC_DRAW);

	BindVAO(VBO);
};

void ModelBush::DrawModel() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 8730);
};