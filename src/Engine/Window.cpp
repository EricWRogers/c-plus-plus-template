#include "Window.hpp"

namespace Engine
{
    Window::Window() {}
    Window::~Window() {}

    int Window::Create(const std::string &_name, int _screenWidth,
                       int _screenHeight, unsigned int _currentFlags)
    {
        Uint32 flags = SDL_WINDOW_OPENGL;

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        m_screenWidth = _screenWidth;
        m_screenHeight = _screenHeight;

        flags |= _currentFlags;

        m_sdlWindow = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        _screenWidth, _screenHeight, flags);
        
        if (m_sdlWindow == nullptr)
            FatalError("SDL Window could not be created", 2);
        
        // Create OpenGL Context
        auto glContext = SDL_GL_CreateContext(m_sdlWindow);

        if (glContext == nullptr)
            FatalError("GL context could not be created", 3);

        // load opengl
        GLenum error = glewInit();

        if (error !=  GLEW_OK)
        {
            FatalError("GLEW could not be created", 4);
        }

        std::string openGLVersion = (const char *)glGetString(GL_VERSION);
        Log("OpenGL Version: " + openGLVersion);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

        // VSYNC 0 off 1 on
        SDL_GL_SetSwapInterval(1);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return 0;
    }

    void Window::SetWindowName(const std::string &_name)
    {
        SDL_SetWindowTitle(m_sdlWindow, _name.c_str());
    }

    void Window::SwapBuffer()
    {
        SDL_GL_SwapWindow(m_sdlWindow);
    }

    void Window::MouseLock(bool _isLocked)
    {
        m_mouseLock = _isLocked;

        SDL_CaptureMouse((SDL_bool)m_mouseLock);
        
        SDL_SetRelativeMouseMode((SDL_bool)m_mouseLock);
    }
} // end of Engine namespace