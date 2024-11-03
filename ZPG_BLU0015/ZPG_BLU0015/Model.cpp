#include "Model.h"

Model::Model(){}

Model::Model(std::vector<float> AModel) {

	model = AModel;

	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, AModel.size() * sizeof(float), AModel.data(), GL_STATIC_DRAW);
	
	BindVAO(VBO);

}

void Model::DrawModel() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, model.size() / 6); //mode,first,count
}

void Model::BindVAO(GLuint AVBO) {
	//Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, AVBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

};