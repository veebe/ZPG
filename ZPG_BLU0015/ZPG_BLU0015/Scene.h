#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "Transformation.h"
#include "Camera.h"

using namespace std;

class Scene {
public:
    Scene(GLFWwindow* window);
    void AddDrawableObject(Model* Amodel, ShaderProgram* ASP, Transformation* ATransformation);
    void RemoveDO() { drawableObjects.pop_back(); };
    void Draw();
    void ScaleDrawableObject(int AObject, float AScale);
    void MoveDrawableObject(int AObject, float x, float y, float z);
    void SpinDrawableObject(int AObject, float x, float y, float z);
private:
    GLFWwindow* window;
    vector<DrawableObject*> drawableObjects;
    Camera* camera;
};
