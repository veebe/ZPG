#include "Scene.h"

Scene::Scene(GLFWwindow* window){
    this->window = window;
	this->camera = new Camera();
}

void Scene::AddDrawableModel(Model* Amodel, ShaderProgram* ASP, Material* AMaterial, TransformationComposite* ATransformation) {
	drawableObjects.push_back(new DrawableModel(Amodel, ASP, GetTransformation(ATransformation), GetMaterial(AMaterial)));
}

void Scene::AddDrawableModel(Model* Amodel, ShaderProgram* ASP, TransformationComposite* ATransformation, Material* AMaterial) {
	drawableObjects.push_back(new DrawableModel(Amodel, ASP, GetTransformation(ATransformation), GetMaterial(AMaterial)));
}

void Scene::AddDrawableLightModel(Model* Amodel, ShaderProgram* ASP, Light* ALight, Material* AMaterial, TransformationComposite* ATransformation) {
	Light* DetachedLight = new Light(*ALight);
	lights.push_back(DetachedLight);
	drawableObjects.push_back(new DrawableLightModel(Amodel, ASP, GetTransformation(ATransformation), GetMaterial(AMaterial), DetachedLight));
}

void Scene::AddDrawableLightModel(Model* Amodel, ShaderProgram* ASP, Light* ALight, TransformationComposite* ATransformation, Material* AMaterial) {
	Light* DetachedLight = new Light(*ALight);
	lights.push_back(DetachedLight);
	drawableObjects.push_back(new DrawableLightModel(Amodel, ASP, GetTransformation(ATransformation), GetMaterial(AMaterial), DetachedLight));
}

void Scene::AddDrawableLight(Light* ALight, TransformationComposite* ATransformation) {

	lights.push_back(ALight);
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

Material* Scene::GetMaterial(Material* AMaterial) {
	if (AMaterial)
		return AMaterial;
	return new Material();
}

void Scene::ResizeWindow(int w, int h) {
	this->camera->ResizeWindow(w, h);
}

void Scene::ApplyCamera() {
	for (auto doj : drawableObjects) {
		doj->ApplyCamera(this->camera);
	}
}

void Scene::ClearLight() {
	for (auto doj : drawableObjects) {
		doj->ClearLights();
	}
}

void Scene::ApplyLight() {
	for (auto doj : drawableObjects) {
		for(auto light : lights)
			doj->ApplyLight(light);
	}
}
