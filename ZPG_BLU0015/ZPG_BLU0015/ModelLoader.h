#pragma once

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h> 

#include <glm/gtx/string_cast.hpp>

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags



struct Vertex
{
    float Position[3];
    float Normal[3];
    float Texture[2];
    float Tangent[3];
};

class ModelLoader {
public:
    GLuint Load(std::string fileName);
protected:
    int indicesCount = 0;
};