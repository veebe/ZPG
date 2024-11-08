#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include "Scene.h"
#include "Callbacks.h"

#include "ModelBush.h"
#include "ModelTree.h"
#include "ModelSuzi.h"
#include "ModelSphere.h"

#include "TransformationBuilder.h"
#include "TransformationRandomizer.h"

#include "Light.h"
#include "ShaderProgramBuilder.h"

class Application {
public:
    void Run();
    void CreateModels();
    void Initialization();
    void NextScene();
	void ToggleCursorLock();

	void MoveActiveCameraMouse(double x, double y);
	void MoveActiveCamera(Direction Adirection, double ADeltaTime);
	void SetMouseButtonDown(bool ADown);

	void ResizeWindow(int w, int h);

    static Application& getInstance();
	double GetDeltaTime();
private:

    Application() = default;
	void ProcessInput(GLFWwindow* window);
	float CalculateFPS();

	std::vector<Scene*> scenes;
    GLFWwindow* window;
    Callbacks* callbacks;

    int activeScene = 0;

	bool MouseButtonDown = false;
	bool firstMouse = true;
	double lastX = 0.0f;
	double lastY = 0.0f;


	double lastTime = 0.0f;
	double deltaTime = 0.0f;

};
