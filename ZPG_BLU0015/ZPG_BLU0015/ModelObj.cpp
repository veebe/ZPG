/* Vratislav Blunar - BLU0015 */
#include "ModelObj.h"

ModelObj::ModelObj(std::string AModelFile) {
	VAO = Load(AModelFile);
}

void ModelObj::DrawModel() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
}