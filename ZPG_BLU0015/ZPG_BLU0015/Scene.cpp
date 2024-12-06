#include "Scene.h"
#include "ModelSuzi.h"

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

void Scene::AddDrawableModelTextured(Model* Amodel, ShaderProgram* ASP, Texture* ATexture, TransformationComposite* ATransformation, Material* AMaterial) {
	drawableObjects.push_back(new DrawableModelTextured(Amodel,ASP, GetTransformation(ATransformation), GetMaterial(AMaterial), ATexture));
}

void Scene::AddDrawableLightModel(Model* Amodel, ShaderProgram* ASP, Light* ALight, Material* AMaterial, TransformationComposite* ATransformation) {
	if (ALight->GetLightType() == REFLECTOR) {
		AddLight(ALight);
		return;
	}
	Light* DetachedLight = new Light(*ALight);
	lights.push_back(DetachedLight);
	drawableObjects.push_back(new DrawableLightModel(Amodel, ASP, GetTransformation(ATransformation), GetMaterial(AMaterial), DetachedLight));
}

void Scene::AddDrawableLightModel(Model* Amodel, ShaderProgram* ASP, Light* ALight, TransformationComposite* ATransformation, Material* AMaterial) {
	if (ALight->GetLightType() == REFLECTOR) {
		AddLight(ALight);
		return;
	}
	Light* DetachedLight = new Light(*ALight);
	lights.push_back(DetachedLight);
	drawableObjects.push_back(new DrawableLightModel(Amodel, ASP, GetTransformation(ATransformation), GetMaterial(AMaterial), DetachedLight));
}

void Scene::AddDrawableLight(Light* ALight, TransformationComposite* ATransformation) {
	if (ALight->GetLightType() == REFLECTOR) {
		AddLight(ALight);
		return;
	}
	lights.push_back(ALight);
	drawableObjects.push_back(new DrawableLight(ALight, GetTransformation(ATransformation)));
}

void Scene::AddDrawableSky(Model* Amodel, ShaderProgram* ASP, Texture* ATexture) {
	this->drawableSky = new DrawableModelTextured(Amodel, ASP, GetTransformation(nullptr), GetMaterial(nullptr), ATexture);
}

void Scene::AddLight(Light* ALight) {
	lights.push_back(ALight);
}
    
void Scene::Draw() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (this->drawableSky){
		glDepthMask(GL_FALSE);
		this->drawableSky->DrawObject();
		glDepthMask(GL_TRUE);
	}
	int a = 1;
	for (auto* dro : drawableObjects)
	{
		glStencilFunc(GL_ALWAYS, a, 0xFF);
		dro->DrawObject();
		a++;
	}
	glfwPollEvents();
	glfwSwapBuffers(window);

};

void Scene::SetInsertableModel(DrawableModel* AObject) {
	this->InsetableObject = AObject;
}

void Scene::Clicked(ClickMode Amode, int AStencilId, glm::vec3 AscreenX) {
	switch (Amode)
	{
	case INSERT:
		{
			glm::vec3 pos = this->camera->CalculateClickedPos(AscreenX);

			TransformationComposite* ltc = new  TransformationComposite();
			ltc->AddTransformation(new TransformationTranslate(pos.x, pos.y, pos.z));
			InsetableObject->SetNewTransformation(ltc);

			drawableObjects.push_back(InsetableObject->clone());

			ClearLight();
			ApplyCamera();
			ApplyLight();

			break;
		}
	case DELETE:
		{
			if (AStencilId > 0)
				DeleteModel(AStencilId);
			break;
		}
	case MOVE:
		{
			if (firstMove){
				movingObject = AStencilId;
				firstMove = !firstMove;
			}
			else
			{
				glm::vec3 pos = this->camera->CalculateClickedPos(AscreenX);

				TransformationComposite* ltc = new  TransformationComposite();
				ltc->AddTransformation(new TransformationTranslate(pos.x, pos.y, pos.z));

				drawableObjects[movingObject -1]->SetNewTransformation(ltc);

				movingObject = 0;
				firstMove = !firstMove;
			}
		}
		break;
	default:
		break;
	}

	
	//printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
}

void Scene::DeleteModel(int AStendilId) {
	drawableObjects.erase(drawableObjects.begin() + AStendilId - 1);
}


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

void Scene::ShowSkyCube() {
	showSkyCube = !showSkyCube;
	if (this->drawableSky)
		this->drawableSky->ShowSkyCube(showSkyCube);
}

void Scene::ApplyCamera() {
	if(this->drawableSky)
		this->drawableSky->ApplyCamera(this->camera);
	for (auto doj : drawableObjects) {
		doj->ApplyCamera(this->camera);
	}
	for (auto light : lights) {
		ReflectorLight* reflector = dynamic_cast<ReflectorLight*>(light);
		if (reflector) {
			reflector->AddCamera(this->camera);
		}
	}
}

void Scene::ClearLight() {
	if(this->drawableSky)
		this->drawableSky->ClearLights();
	for (auto doj : drawableObjects) {
		doj->ClearLights();
	}
}

void Scene::ApplyLight() {
	if (this->drawableSky){
		for (auto light : lights)
			this->drawableSky->ApplyLight(light);
	}
	for (auto doj : drawableObjects) {
		for(auto light : lights)
			doj->ApplyLight(light);
	}
}
