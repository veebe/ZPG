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

	TransformationComposite* tc = new TransformationComposite();
	tc->AddTransformation(new TransformationRotate(1.f, 1.f, 1.f));
	tc->AddTransformation(new TransformationScale(5.f));
	tc->AddTransformation(new TransformationTranslate(1.f, 1.f, 1.f));

	
	scenes[0]->AddDrawableObject(modelSuzi, new ShaderProgram(vertex_shader_color_transform, fragment_shader_normal), tc);

	TransformationComposite* tc2 = dynamic_cast<TransformationComposite*>(tc->Clone());
	tc2->AddTransformation(new TransformationTranslate(5.f,5.f,5.f));
	scenes[0]->AddDrawableObject(modelSphere, new ShaderProgram(vertex_shader_color_transform, fragment_shader_brown), tc2);
	//scenes[0]->AddDrawableObject(modelSuzi, new ShaderProgram(vertex_shader_color_transform, fragment_shader_color), new Transformation());
	/*
	scenes[0]->ScaleDrawableObject(0, 5);
	scenes[0]->SpinDrawableObject(0, 0,0, 3);
	
	scenes[0]->MoveDrawableObject(1, -0.4, -0.4, 0.5);
	scenes[0]->ScaleDrawableObject(1, 0.2);

	scenes[0]->MoveDrawableObject(2, 0.4, -0.4, 0.5);
	scenes[0]->ScaleDrawableObject(2, 0.2);*/
	/*
	scenes[1]->AddDrawableObject(modelTree, new ShaderProgram(vertex_shader_color_transform, fragment_shader_color), new Transformation());
	scenes[1]->AddDrawableObject(modelTree, new ShaderProgram(vertex_shader_color_transform,fragment_shader_brown), new Transformation());
	scenes[1]->AddDrawableObject(modelTree, new ShaderProgram(vertex_shader_color_transform, fragment_shader_green), new Transformation());
	scenes[1]->AddDrawableObject(modelTree, new ShaderProgram(vertex_shader_color_transform, fragment_shader_color), new Transformation());;
	scenes[1]->AddDrawableObject(modelBush, new ShaderProgram(vertex_shader_color_transform, fragment_shader_green), new Transformation());
	

	scenes[1]->AddDrawableObject(modelBush, new ShaderProgram(vertex_shader_color_transform, fragment_shader_color), new Transformation());
	scenes[1]->AddDrawableObject(modelBush, new ShaderProgram(vertex_shader_color_transform, fragment_shader_brown), new Transformation());
	scenes[1]->AddDrawableObject(modelBush, new ShaderProgram(vertex_shader_color_transform, fragment_shader_green), new Transformation());
	scenes[1]->AddDrawableObject(modelBush, new ShaderProgram(vertex_shader_color_transform, fragment_shader_color), new Transformation());
	scenes[1]->AddDrawableObject(modelBush, new ShaderProgram(vertex_shader_color_transform, fragment_shader_green), new Transformation());
	scenes[1]->AddDrawableObject(modelBush, new ShaderProgram(vertex_shader_color_transform, fragment_shader_color), new Transformation());
	scenes[1]->AddDrawableObject(modelTree, new ShaderProgram(vertex_shader_color_transform, fragment_shader_brown), new Transformation());
	

	scenes[1]->MoveDrawableObject(0, -0.9, -0.5, 0);
	scenes[1]->ScaleDrawableObject(0, 0.1);
	scenes[1]->SpinDrawableObject(0,5,5,3);

	scenes[1]->MoveDrawableObject(1, -0.5, -0.55, 1);
	scenes[1]->ScaleDrawableObject(1, 0.16);

	scenes[1]->MoveDrawableObject(2, 0, -0.55, 0);
	scenes[1]->ScaleDrawableObject(2, 0.09);
	scenes[1]->SpinDrawableObject(2, 15, 6, 5);

	scenes[1]->MoveDrawableObject(3, 0.5, -0.5, 0);
	scenes[1]->ScaleDrawableObject(3, 0.2);

	scenes[1]->MoveDrawableObject(4, 1, -0.55, 0);
	scenes[1]->ScaleDrawableObject(4, 0.15);
	scenes[1]->SpinDrawableObject(4, 8, 160, 1);


	scenes[1]->MoveDrawableObject(5, -0.8, -0.55, 0);
	scenes[1]->ScaleDrawableObject(5, 0.4);

	scenes[1]->MoveDrawableObject(6, -0.6, -0.55, 0);
	scenes[1]->ScaleDrawableObject(6, 0.3);

	scenes[1]->MoveDrawableObject(7, 0.1, -0.55, 0);
	scenes[1]->ScaleDrawableObject(7, 0.4);

	scenes[1]->MoveDrawableObject(8, 0.3, -0.55, 0);
	scenes[1]->ScaleDrawableObject(8, 0.3);

	scenes[1]->MoveDrawableObject(9, 0.9, -0.55, 0);
	scenes[1]->ScaleDrawableObject(9, 0.5);
	
	scenes[1]->MoveDrawableObject(10, -0.7, -0.55, 0);
	scenes[1]->ScaleDrawableObject(10, 0.4);

	scenes[1]->MoveDrawableObject(11, -0.1, -0.55, 0);
	scenes[1]->ScaleDrawableObject(11, 0.3);
	*/
}

void Application::ScaleSceneObject(int AObject, float AScale) {
	scenes[activeScene]->ScaleDrawableObject(AObject, AScale);
}

void Application::MoveSceneObject(int AObject, float x, float y, float z) {
	scenes[activeScene]->MoveDrawableObject(AObject, x,y,z);
}

void Application::SpinSceneObject(int AObject, float x, float y, float z) {
	scenes[activeScene]->SpinDrawableObject(AObject, x,y,z);
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