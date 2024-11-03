#pragma once

#include "ShaderProgram.h"
#include "Material.h"

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
    ShaderProgramBuilder& CREATE(SHADERTYPES AST, Material* AMaterial);

    ShaderProgram* Build();

private:
    ShaderProgram* SP;
    const GLchar* AVertexShader = "Shader.vert";

    void CreateShader(SHADERTYPES AST);
};