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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);// GL_FILL);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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

    m_testingShader.Use();
    glBindVertexArray(m_vao);
    //glDrawArrays(GL_TRIANGLES, 0, vertices.size()/6); // Triangles
    //glDrawArrays(GL_LINES, 0, vertices.size()/6); // Lines
    glDrawArrays(GL_LINE_LOOP, 0, vertices.size()/6); // Lines
    glBindVertexArray(0);
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
}