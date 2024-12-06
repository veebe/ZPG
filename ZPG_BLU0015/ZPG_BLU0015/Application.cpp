#include "Application.h"

#include "OtherModels.h"

void Application::Run() {
	scenes[activeScene]->ApplyCamera();
	scenes[activeScene]->ApplyLight();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		float fps = CalculateFPS();
		//printf("FPS: %f\n", fps);

		ProcessInput(this->window);

		scenes[activeScene]->Draw();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::NextScene() {
	if (activeScene + 1 == scenes.size())
		activeScene = 0;
	else
		activeScene++;

	scenes[activeScene]->ClearLight();
	scenes[activeScene]->ApplyCamera();
	scenes[activeScene]->ApplyLight();
}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		MoveActiveCamera(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		MoveActiveCamera(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		MoveActiveCamera(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		MoveActiveCamera(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		MoveActiveCamera(UP, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		MoveActiveCamera(DOWN, deltaTime);
	}
}

void Application::Initialization() {
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	scenes.push_back(new Scene(window));
	scenes.push_back(new Scene(window));
	scenes.push_back(new Scene(window));
	scenes.push_back(new Scene(window));
	scenes.push_back(new Scene(window));
	scenes.push_back(new Scene(window));
	scenes.push_back(new Scene(window));

	callbacks = new Callbacks(window);

	glfwSetWindowUserPointer(window, callbacks);

	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Application::CreateModels() {

	////---------------------------------------------------------------------------------------////
	////                                    common textures                                    ////

	Texture* grassTexture = new Texture("textures/grass.png", GL_TEXTURE0);
	Texture* woodTexture = new Texture("textures/wooden_fence.png", GL_TEXTURE1);
	Texture* skyTexture = new Texture("textures/posx.jpg", "textures/negx.jpg", "textures/posy.jpg", "textures/negy.jpg", "textures/posz.jpg", "textures/negz.jpg", GL_TEXTURE2);
	Texture* houseTexture = new Texture("textures/house.png", GL_TEXTURE3);
	Texture* catTexture = new Texture("textures/Cat_diffuse.jpg", GL_TEXTURE4);
	Texture* utensilsTexture = new Texture("textures/UtensilsJar001_COL_3K.jpg", GL_TEXTURE5);
	Texture* polkaTexture1 = new Texture("textures/polkadot1.png", GL_TEXTURE6);
	Texture* polkaTexture2 = new Texture("textures/polkadot2.png", GL_TEXTURE7);
	Texture* polkaTexture3 = new Texture("textures/polkadot3.jpg", GL_TEXTURE8);

	////---------------------------------------------------------------------------------------////
	////                                     common models                                     ////

	ModelTree* modelTree = new ModelTree;
	ModelBush* modelBush = new ModelBush;
	ModelSuzi* modelSuzi = new ModelSuzi;
	ModelSphere* modelSphere = new ModelSphere;
	Model* modelPlane = new Model(plane);
	Model* modelTriangle = new Model(triangle);

	ModelTextured* modelPlaneUv = new ModelTextured(uv_plane);
	ModelTextured* modelPlaneUv_sm = new ModelTextured(uv_plane_sm);

	Model* modelSkyCube = new ModelSkyCube(skycube);
	Model* modelHouse = new ModelObj("models/house.obj");
	Model* modelLogin = new ModelObj("models/login.obj");
	Model* modelCat = new ModelObj("models/12221_Cat_v1_l3.obj");
	Model* modelUtensils = new ModelObj("models/UtensilsJar001.obj");

	////---------------------------------------------------------------------------------------////
	////                                   common materials                                    ////

	Material* Blue = new Material(glm::vec3(0.1f, 0.1f, 0.7f), glm::vec3(0.1f, 0.1f, 0.2f), 32);
	Material* Red = new Material(glm::vec3(0.7f, 0.1f, 0.1f), glm::vec3(0.2f, 0.1f, 0.1f), 32);
	Material* Green = new Material(glm::vec3(0.1f, 0.7f, 0.1f), glm::vec3(0.1f, 0.2f, 0.1f), 32);
	Material* White = new Material(glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f), 32);
	Material* def = new Material();
	Material* Grey = new Material(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.3, 0.3, 0.3), 8);
	Material* GreyShiny = new Material(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.3, 0.3, 0.3), 50);
	Material* RedDull = new Material(glm::vec3(0.7f, 0.1f, 0.1f), glm::vec3(0.2f, 0.1f, 0.1f), 10);

	TransformationBuilder transformationBuilder;
	ShaderProgramBuilder shaderProgramBuilder;

	////---------------------------------------------------------------------------------------////
	////                                    common shaders                                     ////

	ShaderProgram* constant = shaderProgramBuilder.CREATE(CONSTANT).Build();
	ShaderProgram* lambert = shaderProgramBuilder.CREATE(LAMBERT).Build();
	ShaderProgram* phong = shaderProgramBuilder.CREATE(PHONG).Build();
	ShaderProgram* blinn = shaderProgramBuilder.CREATE(BLINN).Build();
	ShaderProgram* constant_tex = shaderProgramBuilder.CREATE(CONSTANT_TEXTURE).Build();
	ShaderProgram* blinn_tex = shaderProgramBuilder.CREATE(BLINN_TEXTURE).Build();
	ShaderProgram* lambert_tex = shaderProgramBuilder.CREATE(LAMBERT_TEXTURE).Build();
	ShaderProgram* phong_tex = shaderProgramBuilder.CREATE(PHONG_TEXTURE).Build();
	ShaderProgram* skyShader = shaderProgramBuilder.CREATE(SKYCUBE).Build();
	ShaderProgram* skyShaderDynamic = shaderProgramBuilder.CREATE(SKYCUBE_DYNAMIC).Build();
	ShaderProgram* stylizedShader = shaderProgramBuilder.CREATE(STYLIZED).Build();

	////---------------------------------------------------------------------------------------////
	////                                     common lights                                     ////

	Light* whiteLight = new PointLight(glm::vec3(1.0, 1.0, 1.0));
	Light* redLight = new PointLight(glm::vec3(1.0, 0.0, 0.0));
	Light* blueLight = new PointLight(glm::vec3(0.0, 0.0, 1.0));
	Light* greenLight = new PointLight(glm::vec3(0.0, 1.0, 0.0));
	Light* whiteLightReflector = new ReflectorLight(glm::vec3(1.0, 1.0, 1.0));
	Light* sunLight = new DirectionLight(glm::vec3(.8f, .8f, .8f), glm::vec3(-0.0f, -1.0f, -0.0f));
	Light* moonLight = new DirectionLight(glm::vec3(0.1, 0.1, 0.2), glm::vec3(-0.0f, -1.0f, -0.0f));

	////---------------------------------------------------------------------------------------////
	////                               monkey solar system                                     ////

	TransformationComposite* lightTrans = transformationBuilder.SCALE(0.5f).ROTATE(1, 1, 1, true).TRANSLATE(15,2,0).Build();
	scenes[0]->AddDrawableLightModel(modelSphere, constant, whiteLight, White, lightTrans);

	TransformationComposite* sun_t = transformationBuilder
		//.TRANSLATE(0, 0, 0.01, true)
		.ROTATE(0.03f, 0.08f, 0.05f, true)
		.SCALE(4.f)
		.Build();
	scenes[0]->AddDrawableModelTextured(modelSuzi, stylizedShader, polkaTexture3, sun_t, def);

	TransformationComposite* earth_t = transformationBuilder
		//.TRANSLATE(0, 0, 0.01, true)
		.ROTATE(0.f, 0.1f, .03f, true)
		.TRANSLATE(20.f, 0.f, 0.f)
		.ROTATE(0.f, 0.2f, 0.0f, true)
		.Build();
	scenes[0]->AddDrawableModel(modelSuzi, phong, def, earth_t);

	TransformationComposite* moon_t = transformationBuilder
		.COMPONENT(earth_t)
		.SCALE(0.5f)
		.ROTATE(0.f, 0.1f, 0.f, true)
		.TRANSLATE(5.f, -1.f, 5.f)
		.ROTATE(0.f, 0.2f, 0.f, true)
		.Build();
	scenes[0]->AddDrawableModel(modelSuzi, blinn, def, moon_t);

	TransformationComposite* moon_of_moon_t = transformationBuilder
		.COMPONENT(moon_t)
		.SCALE(0.5f)
		.ROTATE(0.3f, 0.0f, 0.3f, true)
		.TRANSLATE(3.f, -1.f, 3.f)
		.ROTATE(0.f, 0.0f, 0.9f, true)
		.Build();
	scenes[0]->AddDrawableModel(modelSuzi, constant, def, moon_of_moon_t);

	scenes[0]->SetInsertableModel(new DrawableModel(modelSuzi, lambert, moon_of_moon_t, def));

	////---------------------------------------------------------------------------------------////
	////                                       forest                                          ////

	for (int i = 0; i < 100; i++)
	{
		scenes[1]->AddDrawableModel(modelTree, phong, TransformationRandomizer::CreateRandomTransformation());
		scenes[1]->AddDrawableModel(modelBush, blinn, Green, TransformationRandomizer::CreateRandomTransformation());

		scenes[1]->AddDrawableModel(modelSphere, constant, TransformationRandomizer::CreateRandomTransformationStars(), White);
	}

	TransformationComposite* planeTransformation = transformationBuilder.SCALE(60).Build();
	scenes[1]->AddDrawableModelTextured(modelPlaneUv, phong_tex, grassTexture, planeTransformation, def);

	scenes[1]->AddDrawableSky(modelSkyCube, skyShaderDynamic, skyTexture);

	TransformationComposite* bug1 = transformationBuilder
		.TRANSLATE(0, 0, 0.005, true)
		.ROTATE(0.f, -0.1f, .0f, true)
		.TRANSLATE(-15.f, 2.f, 0.f)
		.ROTATE(0.f, 0.2f, 0.0f, true)
		.TRANSLATE(10.f, 0.f, 0.f)
		.ROTATE(0.f, 0.2f, 0.0f, true)
		.TRANSLATE(-5.f, 0.f, 0.f)
		.SCALE(0.3f)
		.Build();

	TransformationComposite* bug2 = transformationBuilder
		.ROTATE(0.f, 0.1f, .0f, true)
		.TRANSLATE(10.f, 2.f, 0.f)
		.ROTATE(0.f, 0.2f, 0.0f, true)
		.TRANSLATE(15.f, 0.f, 0.f)
		.ROTATE(0.f, 0.15f, 0.0f, true)
		.TRANSLATE(5.f, 0.f, 0.f)
		.ROTATE(0.f, 0.1f, 0.f, true)
		.TRANSLATE(10.f, 0.f, 0.f)
		.SCALE(0.2f)
		.Build();

	TransformationComposite* bug3 = transformationBuilder
		.ROTATE(0.f, 0.1f, .0f, true)
		.TRANSLATE(5.f, 1.5f, 0.f)
		.ROTATE(0.f, 0.2f, 0.0f, true)
		.TRANSLATE(-8.f, 0.f, 0.f)
		.ROTATE(0.f, 0.15f, 0.0f, true)
		.TRANSLATE(5.f, 0.f, 0.f)
		.ROTATE(0.f, -0.1f, 0.f, true)
		.TRANSLATE(-13.f, 0.f, 0.f)
		.ROTATE(0.f, 0.1f, 0.f, true)
		.TRANSLATE(15.f, 0.f, 0.f)
		.SCALE(0.3f)
		.Build();

	scenes[1]->AddDrawableLightModel(modelSuzi, constant, whiteLight, White, bug1);
	scenes[1]->AddDrawableLightModel(modelSuzi, constant, redLight, Red, bug2);
	scenes[1]->AddDrawableLightModel(modelSuzi, constant, whiteLight, White, bug3);

	scenes[1]->AddLight(whiteLightReflector);

	TransformationComposite* sun = transformationBuilder.ROTATE(0.1f, 0.0f, 0.0f, true).TRANSLATE(0, -60, 0).Build();
	scenes[1]->AddDrawableLightModel(modelSphere,constant, sunLight, sun, White);

	TransformationComposite* moon = transformationBuilder.ROTATE(0.1f, 0.0f, 0.0f, true).TRANSLATE(0, 60, 0).Build();
	scenes[1]->AddDrawableLightModel(modelSphere, lambert, moonLight, moon, Grey);

	TransformationComposite* house_t = transformationBuilder.TRANSLATE(13, 0, -15).ROTATE(0, -45, 0).SCALE(1.3f).Build();
	scenes[1]->AddDrawableModelTextured(modelHouse, lambert_tex, houseTexture, house_t);

	TransformationComposite* login_t = transformationBuilder.ROTATE(.1, 1, 0.1, true).SCALE(.5f).Build();
	scenes[1]->AddDrawableModelTextured(modelLogin, phong_tex, woodTexture, login_t);

	TransformationComposite* cat1_t = transformationBuilder.ROTATE(-90, 0, 0).TRANSLATE(0,3,0).SCALE(0.02).Build();
	scenes[1]->AddDrawableModelTextured(modelCat, lambert_tex, catTexture, cat1_t);

	TransformationComposite* utensils_t = transformationBuilder.TRANSLATE(2, 0, -2).SCALE(2).Build();
	scenes[1]->AddDrawableModelTextured(modelUtensils, phong_tex, utensilsTexture, utensils_t);

	TransformationComposite* monk_t = transformationBuilder.TRANSLATE(10, 10, -10).SCALE(1.5).ROTATE(0,0.2,0,true).Build();
	scenes[1]->AddDrawableModelTextured(modelSuzi, stylizedShader, polkaTexture3, monk_t);

	scenes[1]->SetInsertableModel(new DrawableModel(modelSuzi, lambert, moon_of_moon_t, def));

	////---------------------------------------------------------------------------------------////
	////                                       spheres                                         ////

	TransformationComposite* tc1 = transformationBuilder.TRANSLATE(2, 0, 2).Build();
	TransformationComposite* tc2 = transformationBuilder.TRANSLATE(2, 0, -2).Build();
	TransformationComposite* tc3 = transformationBuilder.TRANSLATE(-2, 0, -2).Build();
	TransformationComposite* tc4 = transformationBuilder.TRANSLATE(-2, 0, 2).Build();

	scenes[2]->AddDrawableModel(modelSphere, phong, tc1);
	scenes[2]->AddDrawableModel(modelSphere, phong, tc2);
	scenes[2]->AddDrawableModel(modelSphere, phong, tc3);
	scenes[2]->AddDrawableModel(modelSphere, phong, tc4);

	TransformationComposite* tclight = transformationBuilder.SCALE(0.1f).TRANSLATE(0,1,0).Build();
	scenes[2]->AddDrawableLightModel(modelSphere, constant, whiteLight, White, tclight);

	TransformationComposite* tclight2 = transformationBuilder.TRANSLATE(0, -10, 0).SCALE(0.1f).Build();
	scenes[2]->AddDrawableLightModel(modelSphere, constant, redLight, Red, tclight2);
	
	scenes[2]->AddLight(whiteLightReflector);
	scenes[2]->SetInsertableModel(new DrawableModel(modelSuzi, lambert, moon_of_moon_t, def));

	////---------------------------------------------------------------------------------------////
	////                                      triangle                                         ////

	scenes[3]->AddDrawableSky(modelSkyCube, skyShader, skyTexture);
	scenes[3]->AddDrawableModel(modelTriangle, constant, Blue);
	scenes[3]->AddDrawableModelTextured(modelPlaneUv_sm, constant_tex, woodTexture, tc1);

	scenes[3]->AddDrawableModelTextured(modelPlaneUv_sm, constant_tex, grassTexture, tc2);
	
	scenes[3]->SetInsertableModel(new DrawableModel(modelSuzi, lambert, moon_of_moon_t, def));
	////---------------------------------------------------------------------------------------////
	////                                   all shaders                                         ////

	TransformationComposite* tc5 = transformationBuilder.ROTATE(180, 5, 45).TRANSLATE(4, 0, 4).Build();
	TransformationComposite* tc6 = transformationBuilder.ROTATE(0,5,10).TRANSLATE(-2, 0, 1).Build();
	TransformationComposite* tc7 = transformationBuilder.ROTATE(1,0,1,true).TRANSLATE(2, 0, 2).Build();


	scenes[4]->AddDrawableModel(modelTree, phong, tc6);
	scenes[4]->AddDrawableModel(modelSphere, lambert, Red);
	scenes[4]->AddDrawableModel(modelSuzi, blinn, tc5);
	scenes[4]->AddDrawableModel(modelTriangle, constant, Blue, tc7);

	scenes[4]->AddDrawableLightModel(modelSphere, constant, whiteLight, White, transformationBuilder.SCALE(0.2f).TRANSLATE(10,5,0).Build());
	scenes[4]->AddLight(sunLight);

	scenes[4]->SetInsertableModel(new DrawableModel(modelSuzi, lambert, moon_of_moon_t, def));

	////---------------------------------------------------------------------------------------////
	////                                      gravity                                          ////


	TransformationComposite* ballPlaneTransformation = transformationBuilder.TRANSLATE(0, -1, 0).SCALE(20).Build();
	scenes[5]->AddDrawableModel(modelPlane, lambert, def, ballPlaneTransformation);

	TransformationComposite* BoundingBallT = transformationBuilder.GRAVITY(-2, 30, -3).ROTATE(1.f,1.f,0,true).Build();
	scenes[5]->AddDrawableModel(modelSuzi, blinn, def, BoundingBallT);

	TransformationComposite* BoundingBallT2 = transformationBuilder.GRAVITY(15, 20, 0,4,80).Build();
	scenes[5]->AddDrawableModel(modelSphere, blinn, Red, BoundingBallT2);

	TransformationComposite* BoundingBallT3 = transformationBuilder.GRAVITY(10, 40, 5,2,95).Build();
	scenes[5]->AddDrawableModel(modelSphere, blinn, Green, BoundingBallT3);

	TransformationComposite* BoundingBallT4 = transformationBuilder.GRAVITY(5, 15, -8).Build();
	scenes[5]->AddDrawableModel(modelSphere, blinn, Blue, BoundingBallT4);
	
	TransformationComposite* BallLightT = transformationBuilder.GRAVITY(5,5,5).TRANSLATE(-0.01f, 0, 0.01f, true).Build();
	scenes[5]->AddDrawableLightModel(modelSphere, constant, whiteLight, BallLightT,White);

	TransformationComposite* BoundingBallT5 = transformationBuilder.GRAVITY(-10, 30, -10,4).ROTATE(0, 1.f, 0, true).TRANSLATE(4, 0, 0).Build();
	scenes[5]->AddDrawableModel(modelSphere, blinn, Blue, BoundingBallT5);

	TransformationComposite* BallLightT2 = transformationBuilder.GRAVITY(-10, 20, -10).Build();
	scenes[5]->AddDrawableLightModel(modelSphere, constant, whiteLight, BallLightT2, White);

	//TransformationComposite* BallLightT3 = transformationBuilder.TRANSLATE(10, 10, 10).Build();
	//scenes[5]->AddDrawableLightModel(modelSuzi, constant, redLight, BallLightT3, Red);
	scenes[5]->SetInsertableModel(new DrawableModel(modelSuzi, lambert, moon_of_moon_t, def));

	////---------------------------------------------------------------------------------------////
	////                                 material spheres                                      ////

	scenes[6]->AddDrawableModel(modelSphere, phong, tc1, Grey);
	scenes[6]->AddDrawableModel(modelSphere, phong, tc2, GreyShiny);
	scenes[6]->AddDrawableModel(modelSphere, phong, tc3, Red);
	scenes[6]->AddDrawableModel(modelSphere, phong, tc4, RedDull);

	scenes[6]->AddDrawableLightModel(modelSphere, constant, whiteLight, White, tclight);
	scenes[6]->SetInsertableModel(new DrawableModel(modelSuzi, lambert, moon_of_moon_t, def));
}

void Application::MoveActiveCameraMouse(double x, double y) {
	if (MouseButtonDown || glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
		if (this->firstMouse)
		{
			this->lastX = x;
			this->lastY = y;
			this->firstMouse = false;
		}
		double xoffset = x - this->lastX;
		double yoffset = this->lastY - y;
		this->lastX = x;
		this->lastY = y;
		scenes[activeScene]->MoveActiveCamera(xoffset, yoffset);
	}
	else
		this->firstMouse = true;
	CursorX = x;
	CursorY = y;
}

void Application::MoveActiveCamera(Direction Adirection, double ADeltaTime) {
	scenes[activeScene]->MoveActiveCamera(Adirection, ADeltaTime);
}

void Application::ToggleCursorLock() {
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Application::SetShowSkyCube() {
	scenes[activeScene]->ShowSkyCube();
}

void Application::SetMouseButtonDown(bool ADown) {
	this->MouseButtonDown = ADown;

	if (ADown){
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		GLint x = (GLint)CursorX;
		GLint y = (GLint)CursorY;

		int newy = windowh - CursorY;

		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
	 
		glm::vec3 screenX = glm::vec3(x, newy, depth);
	/*	glm::mat4 view;
		glm::mat4 projection;
		glm::vec4 viewPort = glm::vec4(0, 0, getResolution().x, getResolution().y);
		glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);
		*/
		//printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

		scenes[activeScene]->Clicked(mode, index, screenX);
	}
}

Application& Application::getInstance()
{
	static Application app;
	return app;
}

void Application::ResizeWindow(int w, int h) {
	windowh = h;
	for (auto s : scenes)
	{
		s->ResizeWindow(w, h);
	}
}

void Application::ChangeClickMode() {
	if (mode == INSERT)
		mode = DELETE;
	else if (mode == DELETE)
		mode = MOVE;
	else if (mode == MOVE)
		mode = INSERT;
}

float Application::CalculateFPS() {
	static int frameCount = 0;
	static double previousTime = 0.0;
	static float fps = 0.0;

	double currentTime = glfwGetTime();
	frameCount++;

	if (currentTime - previousTime >= 1.0) {
		fps = frameCount / (currentTime - previousTime);
		previousTime = currentTime;
		frameCount = 0;
	}
	return fps;
}

double Application::GetDeltaTime() {
	return deltaTime;
}