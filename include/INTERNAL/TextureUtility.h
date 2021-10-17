#include <GL/glew.h>
#include <string>

class Texture
{
    private:
        GLuint m_TextureID;

    private:
        void loadTexture(std::string path);

    public:
        Texture();
        Texture(std::string path);
        GLuint getTextureID();
};