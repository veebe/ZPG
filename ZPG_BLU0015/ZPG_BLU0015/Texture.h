#pragma once
/* Vratislav Blunar - BLU0015 */
#include <GL/glew.h>
#include <GL/GL.h>
#include <SOIL.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

class Texture {
public:
	Texture();
	Texture(const GLchar* ATexture, GLenum ATextureId);
	Texture(const GLchar* ACube1, const GLchar* ACube2, const GLchar* ACube3, const GLchar* ACube4, const GLchar* ACube5, const GLchar* ACube6, GLenum ATextureId);

	int GetTextureId();
protected:
	void LoadTexture();
	void LoadTextures();
	GLenum TextureId;
	std::vector<const GLchar*> TexturePath;
};