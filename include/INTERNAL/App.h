#pragma once

#define Sleep(t) sleep(t)

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <cmath>

#define MAIN(a)         \
    int main()          \
    {                   \
        a *app = new a; \
        app->run(app);  \
        delete app;     \
    }

class App
{
private:
    static void APIENTRY debug_callback(GLenum source,
                                        GLenum type,
                                        GLuint id,
                                        GLenum severity,
                                        GLsizei length,
                                        const GLchar *message,
                                        GLvoid *userParam)
    {
        reinterpret_cast<App *>(userParam)->onDebugMessage(source, type, id, severity, length, message);
    }

public:
    App() {}
    virtual ~App() {}
    virtual void run(App *a)
    {
        bool running = true;
        app = a;

        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        init();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.minorVersion);

        if (info.flags.debug)
        {
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        }
        if (info.flags.robust)
        {
            glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET);
        }
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        // glfwWindowHint(GLFW_SAMPLES, info.samples);
        // glfwWindowHint(GLFW_STEREO, info.flags.stereo ? GL_TRUE : GL_FALSE);
        //        if (info.flags.fullscreen)
        //        {
        //            if (info.windowWidth == 0 || info.windowHeight == 0)
        //            {
        //                GLFWvidmode mode;
        //                glfwGetDesktopMode(&mode);
        //                info.windowWidth = mode.Width;
        //                info.windowHeight = mode.Height;
        //            }
        //
        //            glfwOpenWindow(info.windowWidth, info.windowHeight, 8, 8, 8, 0, 32, 0, GLFW_FULLSCREEN);
        //            glfwSwapInterval((int)info.flags.vsync);
        //        }
        //        else
        {
            window = glfwCreateWindow(info.windowWidth, info.windowHeight, info.title.c_str(), info.flags.fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
            if (!window)
            {
                std::cerr << "Failed to create a new window" << std::endl;
                return;
            }
        }

        glfwMakeContextCurrent(window);

        glfwSetWindowSizeCallback(window, glfw_onResize);
        glfwSetKeyCallback(window, glfw_onKey);
        glfwSetMouseButtonCallback(window, glfw_onMouseButton);
        glfwSetCursorPosCallback(window, glfw_onMouseMove);
        glfwSetScrollCallback(window, glfw_onMouseWheel);
        if (!info.flags.cursor)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }

        // info.flags.stereo = (glfwGetWindowParam(GLFW_STEREO) ? 1 : 0);

        glewInit();

        std::cout << "VENDOR: " << (char *) glGetString(GL_VENDOR) << std::endl;
        std::cout << "VERSION: " << (char *) glGetString(GL_VERSION) << std::endl;
        std::cout << "RENDERER: " << (char *) glGetString(GL_RENDERER) << std::endl;

        if (info.flags.debug)
        {
            if (glewIsSupported("GL_VERSION_4_3"))
            {
                std::cout << "Debug supported" << std::endl;
                glDebugMessageCallback((GLDEBUGPROC)debug_callback, this);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            }
            else if (glewIsExtensionSupported("GL_ARB_debug_output"))
            {
                std::cout << "Debug ARB supported" << std::endl;
                glDebugMessageCallbackARB((GLDEBUGPROC)debug_callback, this);
                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
            }
        }

        startup();

        do
        {
            render(glfwGetTime());
            glfwSwapBuffers(window);
            glfwPollEvents();

            running &= (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE);
            running &= (glfwWindowShouldClose(window) != GL_TRUE);
        } while (running);

        shutdown();

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    virtual void init()
    {
        info.title = "Opengl Playground";
        info.windowWidth = 800;
        info.windowHeight = 600;

        info.majorVersion = 4;
        info.minorVersion = 3;
        info.samples = 0;
        info.flags.all = 0;
        info.flags.cursor = 1;
        info.flags.debug = 1;
    }

    virtual void startup()
    {
    }

    virtual void render(double currentTime)
    {
    }

    virtual void shutdown()
    {
    }

    void setWindowTitle(const char *title)
    {
        glfwSetWindowTitle(window, title);
    }

    virtual void onResize(int w, int h)
    {
        info.windowWidth = w;
        info.windowHeight = h;
    }

    virtual void onKey(int key, int action)
    {

    }

    virtual void onMouseButton(int button, int action)
    {
    }

    virtual void onMouseMove(int x, int y)
    {
    }

    virtual void onMouseWheel(int pos)
    {
    }

    virtual void onDebugMessage(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar *message)
    {
        std::cerr << "Message: " << message << std::endl;
        if(severity == GL_DEBUG_SEVERITY_HIGH)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

    void getMousePosition(int &x, int &y)
    {
        double dx, dy;
        glfwGetCursorPos(window, &dx, &dy);

        x = static_cast<int>(std::floor(dx));
        y = static_cast<int>(std::floor(dy));
    }

public:
    struct APPINFO
    {
        std::string title;
        int windowWidth;
        int windowHeight;
        int majorVersion;
        int minorVersion;
        int samples;
        union
        {
            struct
            {
                unsigned int fullscreen : 1;
                unsigned int vsync : 1;
                unsigned int cursor : 1;
                unsigned int stereo : 1;
                unsigned int debug : 1;
                unsigned int robust : 1;
            };
            unsigned int all;
        } flags;
    };

protected:
    APPINFO info;
    static App *app;
    GLFWwindow *window;

    static void glfw_onResize(GLFWwindow *window, int w, int h)
    {
        app->onResize(w, h);
    }

    static void glfw_onKey(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        app->onKey(key, action);
    }

    static void glfw_onMouseButton(GLFWwindow *window, int button, int action, int mods)
    {
        app->onMouseButton(button, action);
    }

    static void glfw_onMouseMove(GLFWwindow *window, double x, double y)
    {
        app->onMouseMove(static_cast<int>(x), static_cast<int>(y));
    }

    static void glfw_onMouseWheel(GLFWwindow *window, double xoffset, double yoffset)
    {
        app->onMouseWheel(static_cast<int>(yoffset));
    }

    void setVsync(bool enable)
    {
        info.flags.vsync = enable ? 1 : 0;
        glfwSwapInterval((int)info.flags.vsync);
    }
};