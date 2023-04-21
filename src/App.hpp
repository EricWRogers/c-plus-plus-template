#pragma once
#include <vector>
#include "Engine/Debug.hpp"
#include "Engine/Window.hpp"
#include "Engine/Shader.hpp"
#include "Engine/IOManager.hpp"
#include "Engine/Camera.hpp"
#include "Engine/Assets.hpp"
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifdef __linux__
using namespace std::chrono::_V2;
#elif _WIN32
using namespace std::chrono;
#else
using namespace std::chrono;
#endif

enum AppState{
    ON,
    OFF
};

struct PointLightComponent {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct MaterialComponent {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

struct LightMapMaterialComponent {
    int diffuse;
    int specular;
    float shininess;
};

enum BlockTypes
{
  NONE   = 0,
  GRASS  = 1,
  PLANK   = 2
};

class App
{
private:
    void Load();
    void Loop();
    void UpdateLights();
    void Update();
    void Draw();
    void LateUpdate();
    void InputUpdate();

    AppState m_appState = AppState::OFF;
    Engine::Window m_window;
    Engine::Camera m_camera = Engine::Camera(glm::vec3(0.0f, 3.0f, 9.0f));

    high_resolution_clock::time_point currentTime;
    high_resolution_clock::time_point previousTime;

    double deltaTime;

    Engine::GLTexture m_textureMeme  = {};
    Engine::GLTexture m_textureGrass = {};
    Engine::GLTexture m_texturePlank = {};
    Engine::GLTexture m_textureLog   = {};
    Engine::GLTexture m_textureStone = {};
    Engine::GLTexture m_textureBrick = {};
    Engine::GLTexture m_textureGlass = {};
    Engine::GLTexture m_diffuseMap   = {};
    Engine::GLTexture m_specularMap  = {};

    Engine::Shader m_testingShader;
    Engine::Shader m_lightCubeShader;
    Engine::Shader m_lightMapShader;

    Engine::ModelAsset cubeModel;
    const int m_YLayer = 2;
    const int m_ZLayer = 12;
    const int m_XLayer = 12;
    // yzx
    int m_layers[2][12][12] = {
        {
            {01,01,01,01,01,01,01,01,01,01,01,01},
            {01,01,01,01,01,01,01,01,01,01,01,01},
            {01,01,02,02,02,02,02,02,02,02,01,01},
            {01,01,02,02,02,02,02,02,02,02,01,01},
            {01,01,02,02,02,02,02,02,02,02,01,01},
            {01,01,02,02,02,02,02,02,02,02,01,01},
            {01,01,02,02,02,02,02,02,02,02,01,01},
            {01,01,02,02,02,02,02,02,02,02,01,01},
            {01,01,02,02,02,02,02,02,02,02,01,01},
            {01,01,02,02,02,02,02,02,02,02,01,01},
            {01,01,01,01,01,01,01,01,01,01,01,01},
            {01,01,01,01,01,01,01,01,01,01,01,01},
        },
        {
            {00,00,00,00,00,00,00,00,00,00,00,00},
            {00,00,00,00,00,00,00,00,00,00,00,00},
            {00,00,02,02,02,02,02,02,02,02,00,00},
            {00,00,02,00,00,00,00,00,00,02,00,00},
            {00,00,02,00,00,00,00,00,00,02,00,00},
            {00,00,02,00,00,00,00,00,00,02,00,00},
            {00,00,02,00,00,00,00,00,00,02,00,00},
            {00,00,02,00,00,00,00,00,00,02,00,00},
            {00,00,02,00,00,00,00,00,00,02,00,00},
            {00,00,02,02,02,02,02,02,02,02,00,00},
            {00,00,00,00,00,00,00,00,00,00,00,00},
            {00,00,00,00,00,00,00,00,00,00,00,00},
        },
    };

    std::vector<glm::vec3> m_cubeGrass = {
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(-1.0f,-1.0f, 0.0f),
        glm::vec3(-2.0f,-1.0f, 0.0f),
        glm::vec3(-3.0f,-1.0f, 0.0f),
        glm::vec3(-4.0f,-1.0f, 0.0f),
        glm::vec3(-5.0f,-1.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 0.0f),
        glm::vec3(2.0f, -1.0f, 0.0f),
        glm::vec3(3.0f, -1.0f, 0.0f),
        glm::vec3(4.0f, -1.0f, 0.0f),
        glm::vec3(5.0f, -1.0f, 0.0f),

        glm::vec3(5.0f, -1.0f, -1.0f),
        glm::vec3(5.0f, -1.0f, -2.0f),
        glm::vec3(5.0f, -1.0f, -3.0f),
        glm::vec3(5.0f, -1.0f, -4.0f),
        glm::vec3(5.0f, -1.0f, -5.0f),
        glm::vec3(5.0f, -1.0f, -6.0f),
        glm::vec3(5.0f, -1.0f, -7.0f),
        glm::vec3(5.0f, -1.0f, -8.0f),
        glm::vec3(5.0f, -1.0f, -9.0f),
        glm::vec3(5.0f, -1.0f, -10.0f),

        glm::vec3(-5.0f, -1.0f, -1.0f),
        glm::vec3(-5.0f, -1.0f, -2.0f),
        glm::vec3(-5.0f, -1.0f, -3.0f),
        glm::vec3(-5.0f, -1.0f, -4.0f),
        glm::vec3(-5.0f, -1.0f, -5.0f),
        glm::vec3(-5.0f, -1.0f, -6.0f),
        glm::vec3(-5.0f, -1.0f, -7.0f),
        glm::vec3(-5.0f, -1.0f, -8.0f),
        glm::vec3(-5.0f, -1.0f, -9.0f),
        glm::vec3(-5.0f, -1.0f, -10.0f),

        glm::vec3(0.0f, -1.0f, -10.0f),
        glm::vec3(-1.0f,-1.0f, -10.0f),
        glm::vec3(-2.0f,-1.0f, -10.0f),
        glm::vec3(-3.0f,-1.0f, -10.0f),
        glm::vec3(-4.0f,-1.0f, -10.0f),
        glm::vec3(-5.0f,-1.0f, -10.0f),
        glm::vec3(1.0f, -1.0f, -10.0f),
        glm::vec3(2.0f, -1.0f, -10.0f),
        glm::vec3(3.0f, -1.0f, -10.0f),
        glm::vec3(4.0f, -1.0f, -10.0f),
        glm::vec3(5.0f, -1.0f, -10.0f),

    };
    std::vector<glm::vec3> m_cubePlank = {
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(1.0f, 2.0f, -1.0f),
        glm::vec3(1.0f, 3.0f, -1.0f),
        glm::vec3(2.0f, 3.0f, -1.0f),
        glm::vec3(3.0f, 3.0f, -1.0f),
        glm::vec3(3.0f, 2.0f, -1.0f),
        glm::vec3(3.0f, 1.0f, -1.0f),
        glm::vec3(0.0f, 3.0f, -1.0f),
        glm::vec3(0.0f, 2.0f, -1.0f),

        glm::vec3(-1.0f, 1.0f, -1.0f),
        glm::vec3(-1.0f, 2.0f, -1.0f),
        glm::vec3(-1.0f, 3.0f, -1.0f),
        glm::vec3(-2.0f, 3.0f, -1.0f),
        glm::vec3(-3.0f, 3.0f, -1.0f),
        glm::vec3(-3.0f, 2.0f, -1.0f),
        glm::vec3(-3.0f, 1.0f, -1.0f),

        glm::vec3(4.0f, 1.0f, -2.0f),
        glm::vec3(4.0f, 2.0f, -2.0f),
        glm::vec3(4.0f, 3.0f, -2.0f),
        glm::vec3(4.0f, 3.0f, -3.0f),
        glm::vec3(4.0f, 3.0f, -4.0f),
        glm::vec3(4.0f, 3.0f, -5.0f),
        glm::vec3(4.0f, 3.0f, -6.0f),
        glm::vec3(4.0f, 3.0f, -7.0f),
        glm::vec3(4.0f, 3.0f, -8.0f),
        glm::vec3(4.0f, 2.0f, -8.0f),
        glm::vec3(4.0f, 1.0f, -8.0f),

        glm::vec3(3.0f, 1.0f, -9.0f),
        glm::vec3(3.0f, 2.0f, -9.0f),
        glm::vec3(3.0f, 3.0f, -9.0f),
        glm::vec3(2.0f, 3.0f, -9.0f),
        glm::vec3(1.0f, 3.0f, -9.0f),
        glm::vec3(0.0f, 3.0f, -9.0f),
        glm::vec3(-1.0f, 3.0f, -9.0f),
        glm::vec3(-2.0f, 3.0f, -9.0f),
        glm::vec3(-3.0f, 3.0f, -9.0f),
        glm::vec3(-3.0f, 2.0f, -9.0f),
        glm::vec3(-3.0f, 1.0f, -9.0f),

        glm::vec3(-4.0f, 1.0f, -8.0f),
        glm::vec3(-4.0f, 2.0f, -8.0f),
        glm::vec3(-4.0f, 3.0f, -8.0f),
        glm::vec3(-4.0f, 3.0f, -7.0f),
        glm::vec3(-4.0f, 3.0f, -6.0f),
        glm::vec3(-4.0f, 3.0f, -5.0f),
        glm::vec3(-4.0f, 3.0f, -4.0f),
        glm::vec3(-4.0f, 3.0f, -3.0f),
        glm::vec3(-4.0f, 3.0f, -2.0f),
        glm::vec3(-4.0f, 2.0f, -2.0f),
        glm::vec3(-4.0f, 1.0f, -2.0f),
    };
    std::vector<glm::vec3> m_cubeGlass = {
        glm::vec3(2.0f, 1.0f, -1.0f),
        glm::vec3(2.0f, 2.0f, -1.0f),

        glm::vec3(-2.0f, 1.0f, -1.0f),
        glm::vec3(-2.0f, 2.0f, -1.0f),

        glm::vec3(4.0f, 2.0f, -3.0f),
        glm::vec3(4.0f, 1.0f, -3.0f),
        glm::vec3(4.0f, 1.0f, -4.0f),
        glm::vec3(4.0f, 2.0f, -4.0f),
        glm::vec3(4.0f, 2.0f, -5.0f),
        glm::vec3(4.0f, 1.0f, -5.0f),
        glm::vec3(4.0f, 1.0f, -6.0f),
        glm::vec3(4.0f, 2.0f, -6.0f),
        glm::vec3(4.0f, 2.0f, -7.0f),
        glm::vec3(4.0f, 1.0f, -7.0f),

        glm::vec3(2.0f, 1.0f, -9.0f),
        glm::vec3(2.0f, 2.0f, -9.0f),
        glm::vec3(1.0f, 2.0f, -9.0f),
        glm::vec3(1.0f, 1.0f, -9.0f),
        glm::vec3(0.0f, 1.0f, -9.0f),
        glm::vec3(0.0f, 2.0f, -9.0f),
        glm::vec3(-1.0f, 2.0f, -9.0f),
        glm::vec3(-1.0f, 1.0f, -9.0f),
        glm::vec3(-2.0f, 1.0f, -9.0f),
        glm::vec3(-2.0f, 2.0f, -9.0f),

        glm::vec3(-4.0f, 1.0f, -7.0f),
        glm::vec3(-4.0f, 2.0f, -7.0f),
        glm::vec3(-4.0f, 2.0f, -6.0f),
        glm::vec3(-4.0f, 1.0f, -6.0f),
        glm::vec3(-4.0f, 1.0f, -5.0f),
        glm::vec3(-4.0f, 2.0f, -5.0f),
        glm::vec3(-4.0f, 2.0f, -4.0f),
        glm::vec3(-4.0f, 1.0f, -4.0f),
        glm::vec3(-4.0f, 1.0f, -3.0f),
        glm::vec3(-4.0f, 2.0f, -3.0f),
    };
    std::vector<glm::vec3> m_cubeBrick = {
        glm::vec3(3.0f, 4.0f, -2.0f),
        glm::vec3(2.0f, 4.0f, -2.0f),
        glm::vec3(1.0f, 4.0f, -2.0f),
        glm::vec3(0.0f, 4.0f, -2.0f),
        glm::vec3(-1.0f, 4.0f, -2.0f),
        glm::vec3(-2.0f, 4.0f, -2.0f),
        glm::vec3(-3.0f, 4.0f, -2.0f),
        glm::vec3(-3.0f, 4.0f, -3.0f),
        glm::vec3(-3.0f, 4.0f, -4.0f),
        glm::vec3(-3.0f, 4.0f, -5.0f),
        glm::vec3(-3.0f, 4.0f, -6.0f),
        glm::vec3(-3.0f, 4.0f, -7.0f),
        glm::vec3(-3.0f, 4.0f, -8.0f),
        glm::vec3(-2.0f, 4.0f, -8.0f),
        glm::vec3(-1.0f, 4.0f, -8.0f),
        glm::vec3(0.0f, 4.0f, -8.0f),
        glm::vec3(1.0f, 4.0f, -8.0f),
        glm::vec3(2.0f, 4.0f, -8.0f),
        glm::vec3(3.0f, 4.0f, -8.0f),
        glm::vec3(3.0f, 4.0f, -7.0f),
        glm::vec3(3.0f, 4.0f, -6.0f),
        glm::vec3(3.0f, 4.0f, -5.0f),
        glm::vec3(3.0f, 4.0f, -4.0f),
        glm::vec3(3.0f, 4.0f, -3.0f),
        glm::vec3(3.0f, 4.0f, -2.0f),

        glm::vec3(2.0f, 5.0f, -3.0f),
        glm::vec3(1.0f, 5.0f, -3.0f),
        glm::vec3(0.0f, 5.0f, -3.0f),
        glm::vec3(-1.0f, 5.0f, -3.0f),
        glm::vec3(-2.0f, 5.0f, -3.0f),
        glm::vec3(-2.0f, 5.0f, -4.0f),
        glm::vec3(-1.0f, 5.0f, -4.0f),
        glm::vec3(0.0f, 5.0f, -4.0f),
        glm::vec3(1.0f, 5.0f, -4.0f),
        glm::vec3(2.0f, 5.0f, -4.0f),
        glm::vec3(2.0f, 5.0f, -5.0f),
        glm::vec3(1.0f, 5.0f, -5.0f),
        glm::vec3(0.0f, 5.0f, -5.0f),
        glm::vec3(-1.0f, 5.0f, -5.0f),
        glm::vec3(-2.0f, 5.0f, -5.0f),
        glm::vec3(-2.0f, 5.0f, -6.0f),
        glm::vec3(-1.0f, 5.0f, -6.0f),
        glm::vec3(0.0f, 5.0f, -6.0f),
        glm::vec3(1.0f, 5.0f, -6.0f),
        glm::vec3(2.0f, 5.0f, -6.0f),
        glm::vec3(2.0f, 5.0f, -7.0f),
        glm::vec3(1.0f, 5.0f, -7.0f),
        glm::vec3(0.0f, 5.0f, -7.0f),
        glm::vec3(-1.0f, 5.0f, -7.0f),
        glm::vec3(-2.0f, 5.0f, -7.0f),
    };
    std::vector<glm::vec3> m_cubeLog = {
        glm::vec3(4.0f, 0.0f, -1.0f),
        glm::vec3(4.0f, 1.0f, -1.0f),
        glm::vec3(4.0f, 2.0f, -1.0f),
        glm::vec3(4.0f, 3.0f, -1.0f),

        glm::vec3(4.0f, 0.0f, -9.0f),
        glm::vec3(4.0f, 1.0f, -9.0f),
        glm::vec3(4.0f, 2.0f, -9.0f),
        glm::vec3(4.0f, 3.0f, -9.0f),

        glm::vec3(-4.0f, 0.0f, -1.0f),
        glm::vec3(-4.0f, 1.0f, -1.0f),
        glm::vec3(-4.0f, 2.0f, -1.0f),
        glm::vec3(-4.0f, 3.0f, -1.0f),

        glm::vec3(-4.0f, 0.0f, -9.0f),
        glm::vec3(-4.0f, 1.0f, -9.0f),
        glm::vec3(-4.0f, 2.0f, -9.0f),
        glm::vec3(-4.0f, 3.0f, -9.0f),
    };
    std::vector<glm::vec3> m_cubeStone = {
        glm::vec3(0.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f,-1.0f, -1.0f),
        glm::vec3(-2.0f,-1.0f, -1.0f),
        glm::vec3(-3.0f,-1.0f, -1.0f),
        glm::vec3(-4.0f,-1.0f, -1.0f),
        glm::vec3(-5.0f,-1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(2.0f, -1.0f, -1.0f),
        glm::vec3(3.0f, -1.0f, -1.0f),
        glm::vec3(4.0f, -1.0f, -1.0f),

        glm::vec3(-1.0f, 0.0f, -1.0f),
        glm::vec3(-2.0f, 0.0f, -1.0f),
        glm::vec3(-3.0f, 0.0f, -1.0f),
        glm::vec3(1.0f,  0.0f, -1.0f),
        glm::vec3(2.0f,  0.0f, -1.0f),
        glm::vec3(3.0f,  0.0f, -1.0f),

        glm::vec3(0.0f, -1.0f, -2.0f),
        glm::vec3(-1.0f,-1.0f, -2.0f),
        glm::vec3(-2.0f,-1.0f, -2.0f),
        glm::vec3(-3.0f,-1.0f, -2.0f),
        glm::vec3(-4.0f,-1.0f, -2.0f),
        glm::vec3(-5.0f,-1.0f, -2.0f),
        glm::vec3(1.0f, -1.0f, -2.0f),
        glm::vec3(2.0f, -1.0f, -2.0f),
        glm::vec3(3.0f, -1.0f, -2.0f),
        glm::vec3(4.0f, -1.0f, -2.0f),
        
        glm::vec3(4.0f, 0.0f, -2.0f),
        glm::vec3(-4.0f,0.0f, -2.0f),

        glm::vec3(0.0f, -1.0f, -3.0f),
        glm::vec3(-1.0f,-1.0f, -3.0f),
        glm::vec3(-2.0f,-1.0f, -3.0f),
        glm::vec3(-3.0f,-1.0f, -3.0f),
        glm::vec3(-4.0f,-1.0f, -3.0f),
        glm::vec3(-5.0f,-1.0f, -3.0f),
        glm::vec3(1.0f, -1.0f, -3.0f),
        glm::vec3(2.0f, -1.0f, -3.0f),
        glm::vec3(3.0f, -1.0f, -3.0f),
        glm::vec3(4.0f, -1.0f, -3.0f),
        
        glm::vec3(4.0f, 0.0f, -3.0f),
        glm::vec3(-4.0f,0.0f, -3.0f),

        glm::vec3(0.0f, -1.0f, -4.0f),
        glm::vec3(-1.0f,-1.0f, -4.0f),
        glm::vec3(-2.0f,-1.0f, -4.0f),
        glm::vec3(-3.0f,-1.0f, -4.0f),
        glm::vec3(-4.0f,-1.0f, -4.0f),
        glm::vec3(-5.0f,-1.0f, -4.0f),
        glm::vec3(1.0f, -1.0f, -4.0f),
        glm::vec3(2.0f, -1.0f, -4.0f),
        glm::vec3(3.0f, -1.0f, -4.0f),
        glm::vec3(4.0f, -1.0f, -4.0f),

        glm::vec3(-4.0f,0.0f, -4.0f),
        glm::vec3(4.0f, 0.0f, -4.0f),

        glm::vec3(0.0f, -1.0f, -5.0f),
        glm::vec3(-1.0f,-1.0f, -5.0f),
        glm::vec3(-2.0f,-1.0f, -5.0f),
        glm::vec3(-3.0f,-1.0f, -5.0f),
        glm::vec3(-4.0f,-1.0f, -5.0f),
        glm::vec3(-5.0f,-1.0f, -5.0f),
        glm::vec3(1.0f, -1.0f, -5.0f),
        glm::vec3(2.0f, -1.0f, -5.0f),
        glm::vec3(3.0f, -1.0f, -5.0f),
        glm::vec3(4.0f, -1.0f, -5.0f),

        glm::vec3(-4.0f,0.0f, -5.0f),
        glm::vec3(4.0f, 0.0f, -5.0f),

        glm::vec3(0.0f, -1.0f, -6.0f),
        glm::vec3(-1.0f,-1.0f, -6.0f),
        glm::vec3(-2.0f,-1.0f, -6.0f),
        glm::vec3(-3.0f,-1.0f, -6.0f),
        glm::vec3(-4.0f,-1.0f, -6.0f),
        glm::vec3(-5.0f,-1.0f, -6.0f),
        glm::vec3(1.0f, -1.0f, -6.0f),
        glm::vec3(2.0f, -1.0f, -6.0f),
        glm::vec3(3.0f, -1.0f, -6.0f),
        glm::vec3(4.0f, -1.0f, -6.0f),

        glm::vec3(4.0f, 0.0f, -6.0f),
        glm::vec3(-4.0f,0.0f, -6.0f),

        glm::vec3(0.0f, -1.0f, -7.0f),
        glm::vec3(-1.0f,-1.0f, -7.0f),
        glm::vec3(-2.0f,-1.0f, -7.0f),
        glm::vec3(-3.0f,-1.0f, -7.0f),
        glm::vec3(-4.0f,-1.0f, -7.0f),
        glm::vec3(-5.0f,-1.0f, -7.0f),
        glm::vec3(1.0f, -1.0f, -7.0f),
        glm::vec3(2.0f, -1.0f, -7.0f),
        glm::vec3(3.0f, -1.0f, -7.0f),
        glm::vec3(4.0f, -1.0f, -7.0f),

        glm::vec3(-4.0f, 0.0f, -7.0f),
        glm::vec3(4.0f,  0.0f, -7.0f),

        glm::vec3(0.0f, -1.0f, -8.0f),
        glm::vec3(-1.0f,-1.0f, -8.0f),
        glm::vec3(-2.0f,-1.0f, -8.0f),
        glm::vec3(-3.0f,-1.0f, -8.0f),
        glm::vec3(-4.0f,-1.0f, -8.0f),
        glm::vec3(-5.0f,-1.0f, -8.0f),
        glm::vec3(1.0f, -1.0f, -8.0f),
        glm::vec3(2.0f, -1.0f, -8.0f),
        glm::vec3(3.0f, -1.0f, -8.0f),
        glm::vec3(4.0f, -1.0f, -8.0f),

        glm::vec3(4.0f, 0.0f, -8.0f),
        glm::vec3(-4.0f,0.0f, -8.0f),

        glm::vec3(0.0f, -1.0f, -9.0f),
        glm::vec3(-1.0f,-1.0f, -9.0f),
        glm::vec3(-2.0f,-1.0f, -9.0f),
        glm::vec3(-3.0f,-1.0f, -9.0f),
        glm::vec3(-4.0f,-1.0f, -9.0f),
        glm::vec3(-5.0f,-1.0f, -9.0f),
        glm::vec3(1.0f, -1.0f, -9.0f),
        glm::vec3(2.0f, -1.0f, -9.0f),
        glm::vec3(3.0f, -1.0f, -9.0f),
        glm::vec3(4.0f, -1.0f, -9.0f),

        glm::vec3(0.0f,  0.0f, -9.0f),
        glm::vec3(-1.0f, 0.0f, -9.0f),
        glm::vec3(-2.0f, 0.0f, -9.0f),
        glm::vec3(-3.0f, 0.0f, -9.0f),
        glm::vec3(1.0f,  0.0f, -9.0f),
        glm::vec3(2.0f,  0.0f, -9.0f),
        glm::vec3(3.0f,  0.0f, -9.0f),
    };


    // Cube
    std::vector<float> vertices = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  -1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  -1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  -1.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  -1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  -1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

public:
    App();
    ~App();

    void Run();
};