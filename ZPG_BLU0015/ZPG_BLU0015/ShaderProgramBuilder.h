#pragma once

#include "ShaderProgram.h"

enum SHADERTYPES {
    CONSTANT,
    LAMBERT,
    PHONG,
    BLINN
};

class ShaderProgramBuilder {
public:
    ShaderProgramBuilder();

    ShaderProgramBuilder& CREATE(SHADERTYPES AST);

    ShaderProgram* Build();

private:
    ShaderProgram* SP;
    const GLchar* AVertexShader = "Shader.vert";

    void CreateShader(SHADERTYPES AST);
};