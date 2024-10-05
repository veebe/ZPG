#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>  

#include "Scene.h"
#include "Callbacks.h"

class Application {
public:
    Application();
    void Run();
    void CreateModels();
    void Initialization();
private:
    Scene* scene;
    GLFWwindow* window;
    Callbacks* callbacks;
};
