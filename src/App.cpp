#include "App.hpp"
#include "Engine/Engine.hpp"

App::App() {
    Engine::Log("Object Made");
}

App::~App() {
    Engine::Log("Object Destroyed");
}

void App::Run() {
    if (m_appState == AppState::ON)
        Engine::FatalError("App already running.", 1);
    
    Engine::Init();

    // unsigned int windowFlags = 0u;

    // windowFlags |= Engine::WindowFlags::FULLSCREEN;

    m_window.Create("Engine", 800, 600, 0u);
    
    Load();

    m_appState = AppState::ON;

    Loop();
}

void App::Load() {
    // configure opengle global state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // build and compile our shader program
    m_testingShader.Compile("assets/shaders/final.vs" ,"assets/shaders/final.fs");
    m_testingShader.Link();

    m_lightCubeShader.Compile("assets/shaders/light_cube.vs" ,"assets/shaders/light_cube.fs");
    m_lightCubeShader.Link();

    m_lightMapShader.Compile("assets/shaders/light_map.vs" ,"assets/shaders/light_map.fs");
    m_lightMapShader.Link();

    // load models
    cubeModel.Load("assets/models/cube.obj");

    // load textures
    m_textureMeme = Engine::LoadImageToGLTexture("assets/textures/ForcePush.png", GL_RGBA, GL_RGBA);
    m_textureGrass = Engine::LoadImageToGLTexture("assets/textures/grass_block_top.png", GL_RGBA, GL_RGBA);
    m_texturePlank = Engine::LoadImageToGLTexture("assets/textures/oak_planks.png", GL_RGBA, GL_RGBA);
    m_textureLog = Engine::LoadImageToGLTexture("assets/textures/oak_log.png", GL_RGBA, GL_RGBA);
    m_textureStone = Engine::LoadImageToGLTexture("assets/textures/cobblestone.png", GL_RGBA, GL_RGBA);
    m_textureBrick = Engine::LoadImageToGLTexture("assets/textures/bricks.png", GL_RGBA, GL_RGBA);
    m_textureGlass = Engine::LoadImageToGLTexture("assets/textures/glass.png", GL_RGBA, GL_RGBA);
    m_diffuseMap = Engine::LoadImageToGLTexture("assets/textures/container2.png", GL_RGBA, GL_RGBA);
    m_specularMap = Engine::LoadImageToGLTexture("assets/textures/container2_specular.png", GL_RGBA, GL_RGBA);
}

void App::Loop() {
    previousTime = high_resolution_clock::now();
    
    while(m_appState == AppState::ON) {
        currentTime = high_resolution_clock::now();
        deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - previousTime).count() / 1000000000.0;
        previousTime = currentTime;
        //Engine::Log(std::to_string(deltaTime));

        Update();
        Draw();

        // Get SDL to swap our buffer
        m_window.SwapBuffer();
        LateUpdate();
        InputUpdate();
    }
}

void DrawCube(glm::mat4 _transform,Engine::Shader *_shader, Engine::ModelAsset *_model, Engine::GLTexture *_texture)
{
    _shader->SetMat4("transform", _transform);

    glBindVertexArray(_model->GetVAO());
    _shader->SetInt("texture1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture->id);
    glDrawArrays(GL_TRIANGLES, 0, _model->GetSize());
    glBindVertexArray(0);
}

void App::UpdateLights() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // light properties
    glm::vec3 lightColor = glm::vec3(1.0f);
    lightColor.r = static_cast<float>(sin(SDL_GetTicks() * 0.002));
    lightColor.g = static_cast<float>(sin(SDL_GetTicks() * 0.0007));
    lightColor.b = static_cast<float>(sin(SDL_GetTicks() * 0.0013));

    glm::mat4 transform = glm::mat4(1.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = m_camera.GetViewMatrix();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f),
        (float)m_window.GetScreenWidth()/(float)m_window.GetScreenHeight(), 0.1f, 100.0f);
    
    m_lightCubeShader.Use();

    m_lightCubeShader.SetVec4("color", glm::vec4(lightColor.r,lightColor.g,lightColor.b,1.0f));

    glm::vec3 lightCubePosition = glm::vec3(6.0f,3.0f,6.0f);
    transform = glm::translate(transform, lightCubePosition);
    transform = glm::scale(transform, glm::vec3(0.2f));

    m_lightCubeShader.SetMat4("view", view);
    m_lightCubeShader.SetMat4("projection", projection);
    m_lightCubeShader.SetMat4("model", transform);

    glBindVertexArray(cubeModel.GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, cubeModel.GetSize());
    glBindVertexArray(0);

    m_lightCubeShader.UnUse();
    
    m_testingShader.Use();

    m_testingShader.SetMat4("view", view);
    m_testingShader.SetMat4("projection", projection);
    m_testingShader.SetVec3("viewPos", m_camera.position);

    m_testingShader.SetVec4("color", glm::vec4(1.0f));
    
    m_testingShader.SetInt("numDirLights", 1);
    m_testingShader.SetVec3("dirLight.direction", glm::vec3(1.0f,-1.0f, 1.0f));
    m_testingShader.SetVec3("dirLight.ambient", glm::vec3(0.8f)/0.9f);
    m_testingShader.SetVec3("dirLight.diffuse", glm::vec3(0.8f));
    m_testingShader.SetVec3("dirLight.specular", glm::vec3(1.0f));

    m_testingShader.SetInt("numPointLights", 1);
    m_testingShader.SetVec3("pointLights[0].position", lightCubePosition);
    m_testingShader.SetVec3("pointLights[0].ambient", lightColor/2.0f);
    m_testingShader.SetVec3("pointLights[0].diffuse", lightColor/3.0f);
    m_testingShader.SetVec3("pointLights[0].specular", glm::vec3(1.0f));
    m_testingShader.SetFloat("pointLights[0].constant", 1.0f);
    m_testingShader.SetFloat("pointLights[0].linear", 0.09f);
    m_testingShader.SetFloat("pointLights[0].quadratic", 0.032f);

    m_testingShader.SetInt("numSpotLights", 0);
}

void App::Update(){}
void App::Draw(){
    UpdateLights();
    // material properties
    m_testingShader.SetVec3("material.ambient", 0.2f, 0.2f, 0.2f);
    m_testingShader.SetVec3("material.diffuse", glm::vec3(0.6f));
    m_testingShader.SetVec3("material.specular", glm::vec3(0.2f));
    m_testingShader.SetFloat("material.shininess", 0.9f*128.0f);

    glm::mat4 transform;

    for (int y = 0; y < m_YLayer; y++)
    {
        for (int x = 0; x < m_XLayer; x++)
        {
            for (int z = 0; z < m_ZLayer; z++)
            {
                transform = glm::mat4(1.0f);
                transform = glm::translate(transform, glm::vec3(x,y,z));

                switch (m_layers[y][z][x])
                {
                case GRASS:
                    DrawCube(transform, &m_testingShader, &cubeModel, &m_textureGrass);
                    break;
                case PLANK:
                    DrawCube(transform, &m_testingShader, &cubeModel, &m_texturePlank);
                    break;
                default:
                    break;
                }
            }
        }
    }
       
    m_testingShader.UnUse();
}
void App::LateUpdate(){}
void App::InputUpdate(){
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT: {
            m_appState = AppState::OFF;
            break;
        }
        case SDL_MOUSEMOTION: {
            if (m_window.GetMouseLock())
            {
                m_camera.ProcessMouseMovement(
                    event.motion.xrel,
                    -event.motion.yrel
                );
            }
            break;
        }
        case SDL_KEYUP: {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                Engine::Log("Swap Mouse");
                m_window.MouseLock(!m_window.GetMouseLock());
            }

            break;
        }
        }
    }

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_W]) {
        m_camera.ProcessKeyboard(Engine::Camera_Movement::FORWARD, deltaTime);
    }
    if (keyState[SDL_SCANCODE_S]) {
        m_camera.ProcessKeyboard(Engine::Camera_Movement::BACKWARD, deltaTime);
    }
    if (keyState[SDL_SCANCODE_A]) {
        m_camera.ProcessKeyboard(Engine::Camera_Movement::LEFT, deltaTime);
    }
    if (keyState[SDL_SCANCODE_D]) {
        m_camera.ProcessKeyboard(Engine::Camera_Movement::RIGHT, deltaTime);
    }
    if (keyState[SDL_SCANCODE_E]) {
        m_camera.ProcessKeyboard(Engine::Camera_Movement::UP, deltaTime);
    }
    if (keyState[SDL_SCANCODE_Q]) {
        m_camera.ProcessKeyboard(Engine::Camera_Movement::DOWN, deltaTime);
    }
}