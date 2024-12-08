/* Vratislav Blunar - BLU0015 */
#include "Texture.h"

Texture::Texture() {

}
Texture::Texture(const GLchar* ATexture, GLenum ATextureId) {
    this->TextureId = ATextureId;
    this->TexturePath.push_back(ATexture);

    LoadTexture();
}

Texture::Texture(const GLchar* ACube1, const GLchar* ACube2, const GLchar* ACube3, const GLchar* ACube4, const GLchar* ACube5, const GLchar* ACube6, GLenum ATextureId) {
    this->TextureId = ATextureId;
    this->TexturePath.push_back(ACube1);
    this->TexturePath.push_back(ACube2);
    this->TexturePath.push_back(ACube3);
    this->TexturePath.push_back(ACube4);
    this->TexturePath.push_back(ACube5);
    this->TexturePath.push_back(ACube6);

    LoadTextures();
}

void Texture::LoadTextures() {
    glActiveTexture(this->TextureId);

    GLuint image = SOIL_load_OGL_cubemap(TexturePath[0], TexturePath[1], TexturePath[2], TexturePath[3], TexturePath[4], TexturePath[5], SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (image == NULL) {
        std::cout << "An error occurred while loading CubeMap." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, image);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

void Texture::LoadTexture() {
    glActiveTexture(this->TextureId);
    
    GLuint textureID1 = SOIL_load_OGL_texture(this->TexturePath[0], SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if (textureID1 == NULL) {
        std::cout << "An error occurred while loading texture." << std::endl;
        exit(EXIT_FAILURE);
    }
    glBindTexture(GL_TEXTURE_2D, textureID1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

int Texture::GetTextureId() {
    return this->TextureId - GL_TEXTURE0;
}