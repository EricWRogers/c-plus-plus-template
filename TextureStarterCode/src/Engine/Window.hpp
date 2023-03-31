#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <string>

#include "Debug.hpp"

namespace Engine
{
    enum WindowFlags
    {
        FULLSCREEN = 1,
        BORDERLESS = 16
    };

    class Window
    {
    private:
        SDL_Window *m_sdlWindow = nullptr;
        int m_screenWidth = 0;
        int m_screenHeight = 0;
    public:
        Window();
        ~Window();

        int Create(const std::string &_name, int _screenWidth,
                            int _screenHeight, unsigned int _currentFlags);
        void SetWindowName(const std::string &_name);

        void SwapBuffer();

        int GetScreenWidth() { return m_screenWidth; }
        int GetScreenHeight() { return m_screenHeight; }
    };
} // end of Engine namespace