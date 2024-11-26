#include "ModelSkyCube.h"

ModelSkyCube::ModelSkyCube(std::vector<float> AModel) {
    model = AModel;

    GLuint VBO = 0;
    glGenBuffers(1, &VBO); 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, AModel.size() * sizeof(float), AModel.data(), GL_STATIC_DRAW);

    BindVAO(VBO);
}

void ModelSkyCube::DrawModel() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, model.size()); //108
}

void ModelSkyCube::BindVAO(GLuint AVBO) {
    VAO = 0;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, AVBO);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
}