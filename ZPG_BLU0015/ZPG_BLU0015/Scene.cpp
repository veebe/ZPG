#include "Scene.h"

Scene::Scene(GLFWwindow* window){
    this->window = window;
	this->camera = new Camera();
}

void Scene::AddDrawableModel(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation) {
	
	drawableObjects.push_back(new DrawableModel(Amodel, ASP, GetTransformation(ATransformation)));
}

void Scene::AddDrawableLightModel(Model* Amodel, ShaderProgram* ASP, Light* ALight, TransformationComposite* ATransformation) {
	
	this->light = ALight;
	drawableObjects.push_back(new DrawableLightModel(Amodel, ASP, GetTransformation(ATransformation), ALight));
}

void Scene::AddDrawableLight(Light* ALight, TransformationComposite* ATransformation) {

	this->light = ALight;
	drawableObjects.push_back(new DrawableLight(ALight, GetTransformation(ATransformation)));
}
    
void Scene::Draw() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto* dro : drawableObjects)
	{
		dro->DrawObject();
	}
	glfwPollEvents();
	glfwSwapBuffers(window);

};

void Scene::MoveActiveCamera(double x, double y) {
	camera->MoveCameraWithMouse(x, y);
}

void Scene::MoveActiveCamera(Direction Adirection, double ADeltaTime) {
	camera->MoveCameraWithArrows(Adirection, ADeltaTime);
}

TransformationComposite* Scene::GetTransformation(TransformationComposite* ATransformation) {
	if (ATransformation)
		return ATransformation;
	return new TransformationComposite();
}

void Scene::ResizeWindow(int w, int h) {
	this->camera->ResizeWindow(w, h);
}

void Scene::ApplyCamera() {
	for (auto doj : drawableObjects) {
		doj->ApplyCamera(this->camera);
	}
}

void Scene::ApplyLight() {
	for (auto doj : drawableObjects) {
		doj->ApplyLight(this->light);
	}
}