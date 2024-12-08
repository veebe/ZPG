#pragma once
/* Vratislav Blunar - BLU0015 */
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <vector>


class Transformation {
public:
	virtual ~Transformation() = default;
	virtual glm::mat4 GetTransformationMatrix() = 0;

	virtual Transformation* Clone() const = 0;
};