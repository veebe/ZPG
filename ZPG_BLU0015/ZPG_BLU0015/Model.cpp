#include "Model.h"

Model::Model(std::vector<float> AModel, ShaderProgram* ASP) {

	model = AModel;

	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, AModel.size() * sizeof(float), AModel.data(), GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	shaderprogram = ASP;
}

void Model::DrawModel() {
	shaderprogram->UseShader();
	glBindVertexArray(VAO);
	// draw triangles
	glDrawArrays(GL_TRIANGLES, 0, model.size() / 3); //mode,first,count
}