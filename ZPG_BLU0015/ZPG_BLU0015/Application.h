#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include "Scene.h"
#include "Callbacks.h"

#include "ModelBush.h"
#include "ModelTree.h"
#include "ModelSuzi.h"
#include "ModelSphere.h"

class Application {
public:
    void Run();
    void CreateModels();
    void Initialization();
    void NextScene();
	void ScaleSceneObject(int AObject, float AScale);
	void MoveSceneObject(int AObject, float x, float y, float z);
	void SpinSceneObject(int AObject, float x, float y, float z);

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static Application& getInstance();
private:

    Application() = default;
	std::vector<Scene*> scenes;
    GLFWwindow* window;
    Callbacks* callbacks;

    int activeScene;

	const char* vertex_shader_basic =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"void main () {"
		"     gl_Position = vec4 (vp, 1.0);"
		"}";

	const char* vertex_shader_color =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"out vec4 color;"
		"void main () {"
		"     gl_Position = vec4 (vp, 1.0);"
		"	  color = gl_Position;"
		"}";

	const char* vertex_shader_color_transform =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vn;"
		"uniform mat4 modelMatrix;"
		"uniform mat4 viewMatrix;"
		"uniform mat4 projectionMatrix;"
		"out vec3 vn_out;"
		"out vec4 color;"
		"void main () {"
		"	  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
		"	  color = gl_Position;"
		"	  vn_out = vn;"	
		"}";


	const char* fragment_shader_color =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 color;"
		"void main () {"
		"     frag_colour = color;"
		"}";

	const char* fragment_shader_normal =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 color;"
		"in vec3 vn_out;"
		"void main () {"
		"     frag_colour = vec4(vn_out, 1.0);"
		"}";

	const char* fragment_shader_green =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 color;"
		"void main () {"
		"     frag_colour = vec4 (0.3, 0.8, 0.2, 1.0);"
		"}";

	const char* fragment_shader_brown =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 color;"
		"void main () {"
		"     frag_colour = vec4 (0.5, 0.0f, 0.0f, 1.0);"
		"}";

	const char* fragment_shader_idk =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 color;"
		"void main () {"
		"     frag_colour = vec4 (0.5, 0.5f, 0.5f, 1.0);"
		"}";

	const char* fragment_shader_white =
		"#version 330\n"
		"out vec4 frag_colour;"
		"in vec4 color;"
		"void main () {"
		"     frag_colour = vec4 (0.9, 0.9f, 0.9f, 1.0);"
		"}";
};
