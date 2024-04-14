#include "app.h"

App::App() : m_direct3d(0), m_main(0), m_window(0), m_engineTimer(0) {}

App::~App() {}

bool App::Initialize() {
    m_window = new Window(1920, 1080, L"Directx 11");
    m_window->SetCursorLocked(true);

    m_direct3d = new Direct3D;
    m_direct3d->Initialize(1920, 1080, true, m_window->GetHWindow(), false, 100.0f, 0.1f);

    m_main = new Game(EngineState(m_direct3d, m_window, m_engineTimer));

    m_engineTimer = new Time(0.3f, 64);

    return true;
}

void App::Run() {
    while (!m_window->ShouldClose()) {
        // Process Events
        m_window->PollEvents();
        if (m_window->KeyDown(VK_ESCAPE)) break;

        bool tick = m_engineTimer->Tick();
        
        //Run Update Loop
        m_main->OnUpdate(EngineState(m_direct3d, m_window, m_engineTimer));

        //Run Fixed Update Loop if Tick Time has passed
        if (tick) m_main->OnFixedUpdate(EngineState(m_direct3d, m_window, m_engineTimer));

        //Run Draw Loop
        m_main->Draw(m_direct3d);
    }
}

void App::Shutdown() {
    m_direct3d->Shutdown();

    m_window->Close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE _hPrevInstance, PWSTR _pCmdLine, int _nCmdShow) {
    App app;

    if (app.Initialize()) {
        app.Run();
    }

    app.Shutdown();

    return 0;
}