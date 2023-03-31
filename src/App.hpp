#pragma once
#include <vector>
#include "Engine/Debug.hpp"
#include "Engine/Window.hpp"
#include "Engine/Shader.hpp"
#include "Engine/IOManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>


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

    Engine::GLTexture m_textureMeme = {};

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

    std::vector<glm::vec3> m_cubePositon = {
        glm::vec3(0.0f),
        glm::vec3(2.0f, 1.0f, -1.0f),
        glm::vec3(-3.0f, -2.0f, 1.0f)
    };

    // Triangles
    std::vector<float> vertices = {
        // positions           // texture coords
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // Lines
    /*std::vector<float> vertices = {
        // positon          // color
        // Head
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right 
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top center
         //
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top center
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    };*/

    // Line Loop
    /*std::vector<float> vertices = {
        // positon          // color
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top center
    };*/

public:
    App();
    ~App();

    void Run();
};