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

    if (!m_TextureID)
    {
        std::cout << "[SOIL ERROR]: Couldn't find texture file: " << path << '\n';
        return;
    }

    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    if(glewIsSupported("GL_EXT_texture_filter_anisotropic"))
    {
        GLfloat afSetting = 0;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &afSetting);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, afSetting);
    }
}

GLuint Texture::getTextureID()
{
    return m_TextureID;
}