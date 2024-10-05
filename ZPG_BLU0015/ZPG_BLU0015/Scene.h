#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Model.h"
#include "ShaderProgram.h"

using namespace std;

class Scene {
public:
    Scene(GLFWwindow* window);
    void AddModel(std::vector<float> Amodel, ShaderProgram* ASP);
    void Draw();
private:
    GLFWwindow* window;
    vector<Model*> models;
};
