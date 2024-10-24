#include "Scene.h"

Scene::Scene(GLFWwindow* window){
    this->window = window;
	this->camera = new Camera();
}

void Scene::AddDrawableObject(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation) {
	drawableObjects.push_back(new DrawableObject(Amodel,ASP,ATransformation, this->camera));

	if (this->light) {
		ASP->AddLight(light);
	}
}
    
void Scene::Draw() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (DrawableObject* dro : drawableObjects)
	{
		dro->DrawObject();
	}
	glfwPollEvents();
	glfwSwapBuffers(window);

};

void Scene::SetLastCursorPosition(float x, float y) {
	this->LastCursorPosition.x = x;
	this->LastCursorPosition.y = y;
}

CurosrPos Scene::GetLastCursorPosition() {
	return LastCursorPosition;
}

void Scene::MoveActiveCamera(double x, double y) {
	camera->MoveCameraWithMouse(x, y);
}

void Scene::MoveActiveCamera(Direction Adirection, float ADeltaTime) {
	camera->MoveCameraWithArrows(Adirection, ADeltaTime);
}

void Scene::AddLight(Light* ALight) {
	this->light = ALight;

	for (auto doj : drawableObjects) {
		doj->AddLight(this->light);
	}
}