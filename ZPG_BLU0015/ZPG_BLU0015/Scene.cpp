#include "Scene.h"



Scene::Scene(GLFWwindow* window){
    this->window = window;
	this->camera = new Camera();
}

void Scene::AddDrawableObject(Model* Amodel, ShaderProgram* ASP, Transformation* ATransformation) {
	drawableObjects.push_back(new DrawableObject(Amodel,ASP,ATransformation, camera));
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

void Scene::ScaleDrawableObject(int AObject, float AScale) {
	if (AObject <= drawableObjects.size() - 1)
		drawableObjects[AObject]->ScaleObject(AScale);
}

void Scene::MoveDrawableObject(int AObject, float x, float y, float z) {
	if (AObject <= drawableObjects.size() - 1)
		drawableObjects[AObject]->MoveObject(x,y,z);
}

void Scene::SpinDrawableObject(int AObject, float x, float y, float z) {
	if (AObject <= drawableObjects.size() - 1)
		drawableObjects[AObject]->SpinObject(x,y,z);
}

void Scene::MoveActiveCamera(double x, double y) {
	camera->MoveCameraWithMouse(x, y);
}

void Scene::MoveActiveCamera(Direction Adirection, float ADeltaTime) {
	camera->MoveCameraWithArrows(Adirection, ADeltaTime);
}