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

	ShaderProgram* sp = new ShaderProgram(vertex_shader_color_transform,fragment_shader_normal);
	ShaderProgram* sp2 = new ShaderProgram(vertex_shader_color_transform, fragment_shader_normal);

	TransformationBuilder builder;

	TransformationComposite* sun_t = builder.ROTATE(0.f, 0.05f, 0.f, true)
											.SCALE(4.f).Build();
	scenes[0]->AddDrawableObject(modelSuzi, sp, sun_t);

	TransformationBuilder builder2;
	TransformationComposite* earth_t = builder2.SCALE(1.f)
											.ROTATE(0.f, 0.1f, 0.0f, true)
											.TRANSLATE(10.f, -1.f, 10.f)
											.ROTATE(0.f, 0.2f, 0.0f, true)
											.Build();
	scenes[0]->AddDrawableObject(modelSuzi, sp, earth_t);
	
	TransformationBuilder builder3;
	TransformationComposite* moon_t = builder3.COMPONENT(earth_t)
											.SCALE(0.5f)
											.ROTATE(0.f, 0.1f, 0.f, true)
											.TRANSLATE(5.f, -1.f, 5.f)
											.ROTATE(0.f, 0.2f, 0.f, true)
											.Build();
	scenes[0]->AddDrawableObject(modelSuzi, sp, moon_t);
	
	TransformationBuilder builder4;
	TransformationBuilder builder5;
	TransformationBuilder builder6;
	TransformationBuilder builder7;
	TransformationBuilder builder8;

	TransformationComposite* tc1 = builder4.Build();
	TransformationComposite* tc2 = builder5.TRANSLATE(5, 1, 4).SCALE(1.5f).Build();
	TransformationComposite* tc3 = builder6.TRANSLATE(2, 1, 10).SCALE(2.f).Build();
	TransformationComposite* tc4 = builder7.TRANSLATE(9, 1, 1).SCALE(2.6f).Build();
	TransformationComposite* tc5 = builder8.TRANSLATE(15, 1, 8).SCALE(1.3f).Build();

	scenes[1]->AddDrawableObject(modelTree, sp2, tc1);
	scenes[1]->AddDrawableObject(modelTree, sp2, tc2);
	scenes[1]->AddDrawableObject(modelTree, sp2, tc3);
	scenes[1]->AddDrawableObject(modelTree, sp2, tc4);
	scenes[1]->AddDrawableObject(modelBush, sp2, tc5);
}

void Application::MoveActiveCamera(double x, double y) {
	scenes[activeScene]->MoveActiveCamera(x, y);
}

void Application::MoveActiveCamera(Direction Adirection, float ADeltaTime) {
	scenes[activeScene]->MoveActiveCamera(Adirection, ADeltaTime);
}

//float Application::GetDeltaTime() {
//	return deltaTime;
//}

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