#include "Application.h"

Application::Application() {

}

void Application::Run() {
	scene->Draw();
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

	scene = new Scene(window);
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
	std::vector<float> points = {
	-0.8f, 0.8f, 0.0f,
	 -0.6f, -0.5f, 0.0f,
	-0.5f, -0.2f, 0.0f
	};

	float points3[] = {
		-0.5f,-0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
	   0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.0f
	};

	std::vector<float> points2 = {
		-0.5f,-0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	   -0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
	   -0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

	typedef struct {
		float position[4];
		float color[4];
	} a;

	const a b[] = {
	   { { -.5f, -.5f, .5f, 1 }, { 1, 1, 0, 1 } },
	   { { -.5f, .5f, .5f, 1 }, { 1, 0, 0, 1 } },
	   { { .5f, .5f, .5f, 1 }, { 0, 0, 0, 1 } },
	   { { .5f, -.5f, .5f, 1 }, { 0, 1, 0, 1 } },
	};

	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"void main () {"
		"     gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* vertex_shader2 =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"out vec4 color;"
		"void main () {"
		"     gl_Position = vec4 (vp, 1.0);"
		"	  color = gl_Position;"
		"}";


	const char* fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (1.0, 1.0, 0.0, 1.0);"
		"}";

	const char* fragment_shader2 =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 color;"
		"void main () {"
		"     frag_colour = color;"
		"}";

	scene->AddModel(points2, new ShaderProgram(vertex_shader2, fragment_shader2));
	scene->AddModel(points, new ShaderProgram(vertex_shader, fragment_shader));
}
