/* Vratislav Blunar - BLU0015 */
#include "ModelTextured.h"

ModelTextured::ModelTextured(std::vector<float> AModel) {
    model = AModel;

    GLuint VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, AModel.size() * sizeof(float), AModel.data(), GL_STATIC_DRAW);

    BindVAO(VBO);
}

void ModelTextured::DrawModel() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, model.size() / 8);
}

void ModelTextured::BindVAO(GLuint AVBO) {
    VAO = 0;
    glGenVertexArrays(1, &VAO); 
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, AVBO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 6));
}