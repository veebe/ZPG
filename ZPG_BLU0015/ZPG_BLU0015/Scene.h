#pragma once

#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "ShaderProgram.h"
#include "DrawableObject.h"
#include "DrawableLight.h"
#include "DrawableLightModel.h"
#include "DrawableModel.h"
#include "TransformationComposite.h"
#include "TransformationRotate.h"
#include "TransformationScale.h"
#include "TransformationTranslate.h"
#include "Light.h"
#include "LightReflector.h"

using namespace std;


class Scene {
public:
    Scene(GLFWwindow* window);
    void AddDrawableModel(Model* Amodel, ShaderProgram* ASP, Material* AMaterial = nullptr,TransformationComposite* ATransformation = nullptr);
    void AddDrawableModel(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation = nullptr, Material * AMaterial = nullptr);
    void AddDrawableLightModel(Model* Amodel, ShaderProgram* ASP, Light* ALight, Material* AMaterial = nullptr, TransformationComposite* ATransformation = nullptr);
    void AddDrawableLightModel(Model* Amodel, ShaderProgram* ASP, Light* ALight, TransformationComposite* ATransformation = nullptr, Material* AMaterial = nullptr);
    void AddDrawableLight(Light* ALight, TransformationComposite* ATransformation = nullptr);
    void AddLight(Light* ALight);

    void Draw();

    void MoveActiveCamera(double x, double y);
    void MoveActiveCamera(Direction Adirection, double ADeltaTime);
    void ResizeWindow(int w, int h);

    void ApplyCamera();
    void ClearLight();
    void ApplyLight();
private:
    TransformationComposite* GetTransformation(TransformationComposite* ATransformation);
    Material* GetMaterial(Material* AMaterial);

    GLFWwindow* window;
    vector<DrawableObject*> drawableObjects;
    Camera* camera;
    vector<Light*> lights;
};
