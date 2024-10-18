#pragma once

#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "TransformationComposite.h"
#include "TransformationRotate.h"
#include "TransformationScale.h"
#include "TransformationTranslate.h"

using namespace std;

struct CurosrPos {
    float x;
    float y;
};

class Scene {
public:
    Scene(GLFWwindow* window);
    void AddDrawableObject(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation);
    void Draw();

    void MoveActiveCamera(double x, double y);
    void MoveActiveCamera(Direction Adirection, float ADeltaTime);

    void SetLastCursorPosition(float x, float y);
    CurosrPos GetLastCursorPosition();
private:
    GLFWwindow* window;
    vector<DrawableObject*> drawableObjects;
    Camera* camera;

    CurosrPos LastCursorPosition;
};
