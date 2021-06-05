#include <INTERNAL/App.h>

class ClearColor : public App
{
    public:
        void render(double time)
        {
            static const GLfloat color [] = {1.0f, 0.5f, 0.0f};
            glClearBufferfv(GL_COLOR, 0, color);
        }
};

MAIN(ClearColor);