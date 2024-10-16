#include "Scene.h"



Scene::Scene(GLFWwindow* window){
    this->window = window;
}

void Scene::AddDrawableObject(Model* Amodel, ShaderProgram* ASP, Transformation* ATransformation) {
	drawableObjects.push_back(new DrawableObject(Amodel,ASP,ATransformation));
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