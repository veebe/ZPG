/* Vratislav Blunar - BLU0015 */
#include "Callbacks.h"
#include "Application.h"
#include "ClickModeType.h"

Callbacks::Callbacks(GLFWwindow* window) {

	this->window = window;

	glfwSetErrorCallback(error_callback);

	
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Callbacks* callbacks = static_cast<Callbacks*>(glfwGetWindowUserPointer(window));
		if (callbacks) {
			callbacks->key_callback(window, key, scancode, action, mods);
		}
	});

	glfwSetCursorPosCallback(window, cursor_callback);

	glfwSetMouseButtonCallback(window, button_callback);

	glfwSetWindowFocusCallback(window, window_focus_callback);

	glfwSetWindowIconifyCallback(window, window_iconify_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);
};

void Callbacks::error_callback(int error, const char* description) { fputs(description, stderr); }

void Callbacks::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	//printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		Application::getInstance().NextScene();
		
	}
	/*
	if (key == GLFW_KEY_W ) { 
		Application::getInstance().MoveActiveCamera(FORWARD, Application::getInstance().GetDeltaTime());
	}

	if (key == GLFW_KEY_S ) {
		
		Application::getInstance().MoveActiveCamera(BACKWARD, Application::getInstance().GetDeltaTime());
	}

	if (key == GLFW_KEY_A ) {
		
		Application::getInstance().MoveActiveCamera(LEFT, Application::getInstance().GetDeltaTime());
	}
	*/
	if (key == GLFW_KEY_I && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		
		Application::getInstance().ChangeClickMode();
	}

	if (key == GLFW_KEY_R && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		//Application::getInstance().SpinSceneObject(0, 0, 1, 0);
	}

	if (key == GLFW_KEY_T && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		Application::getInstance().ToggleCursorLock();
	}

	if (key == GLFW_KEY_U && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		Application::getInstance().SetShowSkyCube();
	}
}

void Callbacks::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Callbacks::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Callbacks::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);

	Application::getInstance().ResizeWindow(width,height);
}

void Callbacks::cursor_callback(GLFWwindow* window, double x, double y) { 
	Application::getInstance().MoveActiveCameraMouse(x, y);
}

void Callbacks::button_callback(GLFWwindow* window, int button, int action, int mode) {
	printf("button_callback [%d,%d,%d]\n", button, action, mode);
	if (button == 1) {
		Application::getInstance().SetMouseButtonDown((action == 1) ? true : false);
	}
	else if (button == 0 && action == 1) {
		Application::getInstance().ClickAction();
	}
		
}