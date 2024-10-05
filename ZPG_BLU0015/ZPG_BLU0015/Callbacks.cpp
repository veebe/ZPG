#include "Callbacks.h"

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
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

}

void Callbacks::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Callbacks::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Callbacks::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Callbacks::cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

void Callbacks::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}