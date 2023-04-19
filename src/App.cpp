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

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // build and compile our shader program
    m_testingShader.Compile("assets/shaders/3.3.shader.vs"
        ,"assets/shaders/3.3.shader.fs");
    // add attributes here
    m_testingShader.Link();

    m_lightCubeShader.Compile("assets/shaders/light_cube.vs"
        ,"assets/shaders/light_cube.fs");
    m_lightCubeShader.Link();

    m_lightMapShader.Compile("assets/shaders/light_map.vs"
        ,"assets/shaders/light_map.fs");
    m_lightMapShader.Link();

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // uv
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

void App::Update(){}
void App::Draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 transform = glm::mat4(1.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = m_camera.GetViewMatrix();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f),
        (float)m_window.GetScreenWidth()/(float)m_window.GetScreenHeight(), 0.1f, 100.0f);
    
    m_lightCubeShader.Use();

    glm::vec3 lightCubePosition = glm::vec3(0.0f,3.0f,-5.0f);
    transform = glm::translate(transform, lightCubePosition);
    transform = glm::scale(transform, glm::vec3(0.2f));

    m_lightCubeShader.SetMat4("view", view);
    m_lightCubeShader.SetMat4("projection", projection);
    m_lightCubeShader.SetMat4("model", transform);

    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/8);
    glBindVertexArray(0);

    m_lightCubeShader.UnUse();
    
    m_testingShader.Use();

    m_testingShader.SetMat4("view", view);
    m_testingShader.SetMat4("projection", projection);
    m_testingShader.SetVec3("viewPos", m_camera.position);

    // light properties
    glm::vec3 lightColor = glm::vec3(1.0f);
    lightColor.r = static_cast<float>(sin(SDL_GetTicks() * 0.002));
    lightColor.g = static_cast<float>(sin(SDL_GetTicks() * 0.0007));
    lightColor.b = static_cast<float>(sin(SDL_GetTicks() * 0.0013));
    
    m_testingShader.SetVec3("directionalLight.direction", glm::vec3(1.0f,-1.0f, 1.0f));
    m_testingShader.SetVec3("directionalLight.ambient", lightColor/0.9f);
    m_testingShader.SetVec3("directionalLight.diffuse", lightColor);
    m_testingShader.SetVec3("directionalLight.specular", glm::vec3(1.0f));

    // material properties
    m_testingShader.SetVec3("material.ambient", 0.2f, 0.2f, 0.2f);
    m_testingShader.SetVec3("material.diffuse", glm::vec3(0.6f));
    m_testingShader.SetVec3("material.specular", glm::vec3(0.2f));
    m_testingShader.SetFloat("material.shininess", 0.9f*128.0f);

    for(glm::vec3 pos : m_cubeGrass)
    {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, pos);

        m_testingShader.SetMat4("transform", transform);

        glBindVertexArray(m_vao);
        m_testingShader.SetInt("texture1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureGrass.id);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/8);
        glBindVertexArray(0);
    }
    for(glm::vec3 pos : m_cubePlank)
    {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, pos);

        m_testingShader.SetMat4("transform", transform);

        glBindVertexArray(m_vao);
        m_testingShader.SetInt("texture1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texturePlank.id);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/8);
        glBindVertexArray(0);
    }
    for(glm::vec3 pos : m_cubeLog)
    {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, pos);

        m_testingShader.SetMat4("transform", transform);

        glBindVertexArray(m_vao);
        m_testingShader.SetInt("texture1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureLog.id);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/8);
        glBindVertexArray(0);
    }
    for(glm::vec3 pos : m_cubeStone)
    {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, pos);

        m_testingShader.SetMat4("transform", transform);

        glBindVertexArray(m_vao);
        m_testingShader.SetInt("texture1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureStone.id);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/8);
        glBindVertexArray(0);
    }
    for(glm::vec3 pos : m_cubeBrick)
    {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, pos);

        m_testingShader.SetMat4("transform", transform);

        glBindVertexArray(m_vao);
        m_testingShader.SetInt("texture1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureBrick.id);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/8);
        glBindVertexArray(0);
    }
    for(glm::vec3 pos : m_cubeGlass)
    {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, pos);

        m_testingShader.SetMat4("transform", transform);

        glBindVertexArray(m_vao);
        m_testingShader.SetInt("texture1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureGlass.id);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/8);
        glBindVertexArray(0);
    }
    
    m_testingShader.UnUse();

    m_lightMapShader.Use();

    m_lightMapShader.SetMat4("view", view);
    m_lightMapShader.SetMat4("projection", projection);
    m_lightMapShader.SetVec3("viewPos", m_camera.position);

    lightColor = glm::vec3(1.0f);

    m_lightMapShader.SetVec3("pointLight.position", lightCubePosition);
    m_lightMapShader.SetVec3("pointLight.ambient", lightColor/0.9f);
    m_lightMapShader.SetVec3("pointLight.diffuse", lightColor);
    m_lightMapShader.SetVec3("pointLight.specular", glm::vec3(1.0f));

    // material properties
    m_lightMapShader.SetInt("material.diffuse", 0);
    m_lightMapShader.SetInt("material.specular", 1);
    m_lightMapShader.SetFloat("material.shininess", 0.9f*128.0f);

    transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -5.0f));

    m_lightMapShader.SetMat4("transform", transform);

    glBindVertexArray(m_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_diffuseMap.id);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_specularMap.id);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/8);
    glBindVertexArray(0);
    
    m_lightMapShader.UnUse();
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