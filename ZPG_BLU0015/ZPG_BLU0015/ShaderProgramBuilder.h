#pragma once
/* Vratislav Blunar - BLU0015 */
#include "ShaderProgram.h"

enum SHADERTYPES {
    CONSTANT,
    LAMBERT,
    PHONG,
    BLINN,
    CONSTANT_TEXTURE,
    PHONG_TEXTURE,
    LAMBERT_TEXTURE,
    BLINN_TEXTURE,
    SKYCUBE,
    SKYCUBE_DYNAMIC,
    STYLIZED
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