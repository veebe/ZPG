#include "Scene.h"



Scene::Scene(GLFWwindow* window){
    this->window = window;
}

void Scene::AddModel(std::vector<float> Amodel, ShaderProgram* ASP) {
	models.push_back(new Model(Amodel, ASP));
}
    
void Scene::Draw() {
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (Model* m : models)
		{
			m->DrawModel();
		}
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
};

