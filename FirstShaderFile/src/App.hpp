#pragma once
#include <iostream>
#include "Engine/Debug.hpp"
#include "Engine/Window.hpp"
#include "Engine/Shader.hpp"


enum AppState{
    ON,
    OFF
};

class App
{
private:
    void Load();
    void Loop();
    void Update();
    void Draw();
    void LateUpdate();
    void InputUpdate();

    AppState m_appState = AppState::OFF;
    Engine::Window m_window;

    unsigned int m_vbo, m_vao;
    unsigned int m_vertexShader, m_shaderProgram;

    Engine::Shader m_testingShader;

    const char *m_vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char *m_fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

public:
    App();
    ~App();

    void Run();
};