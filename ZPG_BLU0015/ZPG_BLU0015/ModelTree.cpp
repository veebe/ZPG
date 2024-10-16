#include "ModelTree.h"

ModelTree::ModelTree() {
	

	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);

	BindVAO(VBO);
};

void ModelTree::DrawModel(){
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 92814);
};