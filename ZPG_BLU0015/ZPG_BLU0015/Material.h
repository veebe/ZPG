#pragma once
/* Vratislav Blunar - BLU0015 */
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vector"

class Material {
public:
	Material();
	Material(glm::vec3 AObjectColor, glm::vec3 AAmbientColor, float AShininess);

	glm::vec3 GetObjectColor();
	glm::vec3 GetAmbientColor();
	float GetShininess();

private:
	glm::vec3 ObjectColor = glm::vec3(0.38f, 0.65f, 0.81f);
	glm::vec3 AmbientColor = glm::vec3(0.1f,0.1f,0.1f);
	float Shininess = 32;
};