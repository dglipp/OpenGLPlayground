#include <INTERNAL/App.h>
#include <cmath>

class ClearColor : public App
{
    public:
        void render(double time)
        {
            const GLfloat color [] = {(float) std::abs(std::sin(time)), 0.5f, 0.0f};
            glClearBufferfv(GL_COLOR, 0, color);
        }
};

MAIN(ClearColor);