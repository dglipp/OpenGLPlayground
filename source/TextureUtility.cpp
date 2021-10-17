#include <INTERNAL/TextureUtility.h>

#include <iostream>

#include <VENDOR/SOIL2/SOIL2.h>

Texture::Texture()
{
}

Texture::Texture(std::string path)
{
    loadTexture(path);
}

void Texture::loadTexture(std::string path)
{
    m_TextureID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    if(!m_TextureID)
        std::cout << "[SOIL ERROR]: Couldn't find texture file: " << path << '\n';
}

GLuint Texture::getTextureID()
{
    return m_TextureID;
}