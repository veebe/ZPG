#include "Application.h"

#include "OtherModels.h"

void Application::Run() {
	scenes[activeScene]->ApplyCamera();
	scenes[activeScene]->ApplyLight();

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

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
	////                                     common models                                     ////

	ModelTree* modelTree = new ModelTree;
	ModelBush* modelBush = new ModelBush;
	ModelSuzi* modelSuzi = new ModelSuzi;
	ModelSphere* modelSphere = new ModelSphere;
	Model* modelPlane = new Model(plane);
	Model* modelTriangle = new Model(triangle);

	Material* Blue = new Material(glm::vec3(0.1f, 0.1f, 0.8f), glm::vec3(0.1f, 0.1f, 0.2f), 32);
	Material* Red = new Material(glm::vec3(0.8f, 0.1f, 0.1f), glm::vec3(0.2f, 0.1f, 0.1f), 16);
	Material* Green = new Material(glm::vec3(0.1f, 0.6f, 0.1f), glm::vec3(0.1f, 0.2f, 0.1f), 8);
	Material* White = new Material(glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 1.f, 1.f), 32);

	TransformationBuilder transformationBuilder;
	ShaderProgramBuilder shaderProgramBuilder;

	ShaderProgram* constantWhite = shaderProgramBuilder.CREATE(CONSTANT, White).Build();
	ShaderProgram* lambert = shaderProgramBuilder.CREATE(LAMBERT).Build();
	ShaderProgram* phong = shaderProgramBuilder.CREATE(PHONG).Build();
	ShaderProgram* blinn = shaderProgramBuilder.CREATE(BLINN).Build();

	ShaderProgram* blinnGreen = shaderProgramBuilder.CREATE(BLINN, Green).Build();
	ShaderProgram* lambertRed = shaderProgramBuilder.CREATE(LAMBERT, Red).Build();
	ShaderProgram* constantBlue = shaderProgramBuilder.CREATE(CONSTANT, Blue).Build();

	Light* whiteLight = new Light(glm::vec3(1.0, 1.0, 1.0));

	////---------------------------------------------------------------------------------------////
	////                               monkey solar system                                     ////

	TransformationComposite* lightTrans = transformationBuilder.SCALE(0.5f).ROTATE(1, 1, 1, true).TRANSLATE(15,2,0).Build();

	scenes[0]->AddDrawableLightModel(modelSphere,constantWhite, whiteLight, lightTrans);

	TransformationComposite* sun_t = transformationBuilder
		//.TRANSLATE(0, 0, 0.01, true)
		.ROTATE(0.03f, 0.08f, 0.05f, true)
		.SCALE(4.f)
		.Build();
	scenes[0]->AddDrawableModel(modelSuzi, lambertRed, sun_t);

	TransformationComposite* earth_t = transformationBuilder
		//.TRANSLATE(0, 0, 0.01, true)
		.ROTATE(0.f, 0.1f, .03f, true)
		.TRANSLATE(20.f, 0.f, 0.f)
		.ROTATE(0.f, 0.2f, 0.0f, true)
		.Build();
	scenes[0]->AddDrawableModel(modelSuzi, phong, earth_t);

	TransformationComposite* moon_t = transformationBuilder
		.COMPONENT(earth_t)
		.SCALE(0.5f)
		.ROTATE(0.f, 0.1f, 0.f, true)
		.TRANSLATE(5.f, -1.f, 5.f)
		.ROTATE(0.f, 0.2f, 0.f, true)
		.Build();
	scenes[0]->AddDrawableModel(modelSuzi, blinn, moon_t);

	TransformationComposite* moon_of_moon_t = transformationBuilder
		.COMPONENT(moon_t)
		.SCALE(0.5f)
		.ROTATE(0.3f, 0.0f, 0.3f, true)
		.TRANSLATE(3.f, -1.f, 3.f)
		.ROTATE(0.f, 0.0f, 0.9f, true)
		.Build();
	scenes[0]->AddDrawableModel(modelSuzi, constantBlue, moon_of_moon_t);

	////---------------------------------------------------------------------------------------////
	////                                       forest                                          ////

	for (int i = 0; i < 100; i++)
	{
		scenes[1]->AddDrawableModel(modelTree, phong, TransformationRandomizer::CreateRandomTransformation());
		scenes[1]->AddDrawableModel(modelBush, blinnGreen, TransformationRandomizer::CreateRandomTransformation());
	}

	TransformationComposite* planeTransformation = transformationBuilder.SCALE(60).Build();

	scenes[1]->AddDrawableModel(modelPlane, lambert, planeTransformation);

	TransformationComposite* lightTransformation = transformationBuilder.ROTATE(0,1,0, true).TRANSLATE(20,20,0).Build();

	scenes[1]->AddDrawableLightModel(modelSuzi, constantWhite, whiteLight, lightTransformation);


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

	TransformationComposite* tclight = transformationBuilder.SCALE(0.1f).Build();

	//scenes[2]->AddDrawableLightModel(modelSphere, constantWhite, whiteLight, tclight);
	scenes[2]->AddDrawableLight(whiteLight, tclight);

	////---------------------------------------------------------------------------------------////
	////                                      triangle                                         ////

	ShaderProgram* constantTriangle = shaderProgramBuilder.CREATE(CONSTANT).Build();

	scenes[3]->AddDrawableModel(modelTriangle, constantBlue);

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

void Application::SetMouseButtonDown(bool ADown) {
	this->MouseButtonDown = ADown;
}

Application& Application::getInstance()
{
	static Application app;
	return app;
}

void Application::ResizeWindow(int w, int h) {
	for (auto s : scenes)
	{
		s->ResizeWindow(w, h);
	}
}