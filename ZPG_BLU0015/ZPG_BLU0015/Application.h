#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include "Scene.h"
#include "Callbacks.h"

#include "ModelBush.h"
#include "ModelTree.h"
#include "ModelSuzi.h"
#include "ModelSphere.h"

#include "TransformationBuilder.h"
#include "TransformationRandomizer.h"

#include "Light.h"


class Application {
public:
    void Run();
    void CreateModels();
    void Initialization();
    void NextScene();
	void ToggleCursorLock();

	void MoveActiveCamera(double x, double y);
	void MoveActiveCamera(Direction Adirection, float ADeltaTime);

	void SetActiveSceneLastCursorPos(float x, float y);

    static Application& getInstance();
private:

    Application() = default;
	void ProcessInput(GLFWwindow* window);
	std::vector<Scene*> scenes;
    GLFWwindow* window;
    Callbacks* callbacks;

    int activeScene;
	float lastTime = 0.0f;
	float deltaTime = 0.0f;

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

	const char* vertex_lamb =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"               
		"layout(location=1) in vec3 vn;"               
		"uniform mat4 modelMatrix;"                    
		"uniform mat4 viewMatrix;"                     
		"uniform mat4 projectionMatrix;"  
		"uniform vec3 cameraPosition;"
		"out vec4 ex_worldPosition;"                   
		"out vec3 ex_worldNormal;"  
		"out vec3 ex_cameraDirection;"
		""
		"void main () {"
		"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
		"    ex_worldPosition = modelMatrix * vec4(vp, 1.0);"
		"    ex_worldNormal = mat3(transpose(inverse(modelMatrix))) * vn;"  
		"    ex_cameraDirection = cameraPosition - vec3(ex_worldPosition);"
		"}";


	const char* fragment_lamb =
		"#version 330\n"
		"in vec4 ex_worldPosition;"
		"in vec3 ex_worldNormal;"
		"in vec3 ex_cameraDirection;"
		"out vec4 frag_colour;"
		"uniform vec3 lightPosition;"   
		""
		"void main () {"
		"	 vec3 lightPosition= vec3(10.0,10.0,10.0);"
		"    vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition));"  
		"    vec3 lightColor = vec3(1.0, 1.0, 1.0);"  
		"    float diff = max(dot(lightVector, normalize(ex_worldNormal)), 0.0);"
		"    vec3 diffuse = diff * lightColor;"  
		""
		"    vec3 ambient = vec3(0.1, 0.1, 0.1);" 
		"    vec3 objectColor = vec3(0.385, 0.647, 0.812);" 
		""
		//"    vec3 viewDir = ex_cameraDirection;"
		//"	 vec3 reflectDir = reflect(-lightVector, vec3(0.0, 1.0, 0.0)); "    
		//"    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);"
		//"    vec4 specular = vec4(lightColor, 1.0) * spec;"
		"    frag_colour = vec4((ambient + diffuse) * objectColor, 1.0);"  
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
