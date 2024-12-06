#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>  
#include <SOIL.h>

#include "Scene.h"
#include "Callbacks.h"

#include "ModelBush.h"
#include "ModelTree.h"
#include "ModelSuzi.h"
#include "ModelSphere.h"
#include "ModelTextured.h"
#include "ModelSkyCube.h"
#include "ModelObj.h"
#include "Texture.h"

#include "TransformationBuilder.h"
#include "TransformationRandomizer.h"

#include "Light.h"
#include "LightReflector.h"
#include "LightPoint.h"
#include "LightDirection.h"
#include "ShaderProgramBuilder.h"

#include "ClickModeType.h"

class Application {
public:
    void Run();
    void CreateModels();
    void Initialization();
    void NextScene();
	void ToggleCursorLock();
	void SetShowSkyCube();

	void MoveActiveCameraMouse(double x, double y);
	void MoveActiveCamera(Direction Adirection, double ADeltaTime);
	void SetMouseButtonDown(bool ADown);
	void ChangeClickMode();

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

	double CursorX = 0.0f;
	double CursorY = 0.0f;
	int windowh = 600;

	double lastTime = 0.0f;
	double deltaTime = 0.0f;

	ClickMode mode = INSERT;
};
