/* Vratislav Blunar - BLU0015 */
#include "ModelSphere.h"

ModelSphere::ModelSphere() {


	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);

	BindVAO(VBO);
};

void ModelSphere::DrawModel() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 2880);
};