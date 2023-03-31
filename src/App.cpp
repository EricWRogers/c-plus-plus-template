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
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // build and compile our shader program
    m_testingShader.Compile("assets/shaders/3.3.shader.vs"
        ,"assets/shaders/3.3.shader.fs");
    // add attributes here
    m_testingShader.Link();

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // uv
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_textureMeme = Engine::LoadImageToGLTexture("assets/textures/ForcePush.png", GL_RGBA, GL_RGBA);
}

void App::Loop() {
    while(m_appState == AppState::ON) {
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
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 transform = glm::mat4(1.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(145.0f),
        (float)m_window.GetScreenWidth()/(float)m_window.GetScreenHeight(), 0.1f, 100.0f);

    m_testingShader.Use();

    m_testingShader.SetMat4("view", view);
    m_testingShader.SetMat4("projection", projection);

    for(glm::vec3 pos : m_cubePositon)
    {
        transform = glm::mat4(1.0f);
        transform = glm::translate(transform, pos);
        transform = glm::rotate(transform, (float)SDL_GetTicks() * 0.001f, glm::vec3(0.0f, 0.0f, 1.0f));

        m_testingShader.SetMat4("transform", transform);

        glBindVertexArray(m_vao);
        m_testingShader.SetInt("texture1", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_textureMeme.id);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/5); // Triangles
        //glDrawArrays(GL_LINES, 0, vertices.size()/6); // Lines
        //glDrawArrays(GL_LINE_LOOP, 0, vertices.size()/6); // Lines
        glBindVertexArray(0);
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
        }
    }

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);

    if (keyState[SDL_SCANCODE_W]) {
        Engine::Log("W Down");
    }
    else {
        Engine::Log("W Up");
    }
}