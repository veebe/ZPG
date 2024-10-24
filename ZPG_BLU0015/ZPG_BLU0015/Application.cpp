#include "Application.h"

void Application::Run() {
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		float currentTime = glfwGetTime();
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

	glfwSetCursorPos(this->window, scenes[activeScene]->GetLastCursorPosition().x, scenes[activeScene]->GetLastCursorPosition().y);
}

void Application::SetActiveSceneLastCursorPos(float x, float y) {
	scenes[activeScene]->SetLastCursorPosition(x, y);
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

	activeScene = 0;

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

	ModelTree* modelTree = new ModelTree;
	ModelBush* modelBush = new ModelBush;
	ModelSuzi* modelSuzi = new ModelSuzi;
	ModelSphere* modelSphere = new ModelSphere;

	ShaderProgram* lambert1 = new ShaderProgram("ShaderLambert.vert", "ShaderLambert.frag");
	ShaderProgram* lambert2 = new ShaderProgram("ShaderLambert.vert", "ShaderLambert.frag");
	ShaderProgram* lambert3 = new ShaderProgram("ShaderLambert.vert", "ShaderLambert.frag");

	TransformationBuilder builder;
	TransformationBuilder builder2;
	TransformationBuilder builder3;

	scenes[0]->AddLight(new Light(glm::vec3(10.0, 10.0, 10.0), glm::vec3(1.0, 1.0, 1.0)));

	TransformationComposite* sun_t = builder.ROTATE(0.f, 0.08f, 0.f, true)
		.SCALE(4.f).Build();
	scenes[0]->AddDrawableObject(modelSuzi, lambert1, sun_t);

	TransformationComposite* earth_t = builder2.SCALE(1.f)
		.ROTATE(0.f, 0.1f, 0.0f, true)
		.TRANSLATE(15.f, -1.f, 15.f)
		.ROTATE(0.f, 0.2f, 0.0f, true)
		.Build();
	scenes[0]->AddDrawableObject(modelSuzi, lambert1, earth_t);

	TransformationComposite* moon_t = builder3.COMPONENT(earth_t)
		.SCALE(0.5f)
		.ROTATE(0.f, 0.1f, 0.f, true)
		.TRANSLATE(5.f, -1.f, 5.f)
		.ROTATE(0.f, 0.2f, 0.f, true)
		.Build();
	scenes[0]->AddDrawableObject(modelSuzi, lambert1, moon_t);

	scenes[1]->AddLight(new Light(glm::vec3(10.0, 10.0, 10.0), glm::vec3(0.1, 0.8, 1.0)));

	for (int i = 0; i < 100; i++)
	{
		scenes[1]->AddDrawableObject(modelTree, lambert2, TransformationRandomizer::CreateRandomTransformation());
		scenes[1]->AddDrawableObject(modelBush, lambert2, TransformationRandomizer::CreateRandomTransformation());
	}

	TransformationComposite* tc1 = new TransformationComposite();
	tc1->AddTransformation(new TransformationTranslate(2,0,2));

	TransformationComposite* tc2 = new TransformationComposite();
	tc2->AddTransformation(new TransformationTranslate(2, 0, -2));

	TransformationComposite* tc3 = new TransformationComposite();
	tc3->AddTransformation(new TransformationTranslate(-2, 0, -2));

	TransformationComposite* tc4 = new TransformationComposite();
	tc4->AddTransformation(new TransformationTranslate(-2, 0, 2));

	scenes[2]->AddDrawableObject(modelSphere, lambert3, tc1);
	scenes[2]->AddDrawableObject(modelSphere, lambert3, tc2);
	scenes[2]->AddDrawableObject(modelSphere, lambert3, tc3);
	scenes[2]->AddDrawableObject(modelSphere, lambert3, tc4);

	scenes[2]->AddLight(new Light(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 1.0)));
}

void Application::MoveActiveCamera(double x, double y) {
	scenes[activeScene]->MoveActiveCamera(x, y);
}

void Application::MoveActiveCamera(Direction Adirection, float ADeltaTime) {
	scenes[activeScene]->MoveActiveCamera(Adirection, ADeltaTime);
}

void Application::ToggleCursorLock() {
	if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_NORMAL)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Application& Application::getInstance()
{
	static Application app;
	return app;
}