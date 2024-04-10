#include "app.h"

App::App() : m_direct3d(0), m_main(0), m_window(0), m_frameTime(0) {}

App::~App() {}

bool App::Initialize() {
    m_window = new Window(1920, 1080, L"Directx 11");
    m_window->SetCursorLocked(true);

    m_direct3d = new Direct3D;
    m_direct3d->Initialize(1920, 1080, true, m_window->GetHWindow(), false, 100.0f, 0.1f);

    m_main = new Game(EngineState(m_direct3d, m_window));

    StartTimer();

    return true;
}

void App::Run() {
    while (!m_window->ShouldClose()) {
        // Process Events
        m_window->PollEvents();
        if (m_window->KeyDown(VK_ESCAPE)) break;
        
        //Run Update Loop
        m_main->OnUpdate(EngineState(m_direct3d, m_window), GetFrameTime());

        //Run Draw Loop
        m_main->Draw(m_direct3d);
        
    }
}

void App::Shutdown() {
    m_direct3d->Shutdown();

    m_window->Close();
}

void App::StartTimer()
{
    LARGE_INTEGER frequencyCount;
    QueryPerformanceFrequency(&frequencyCount);

    m_countsPerSecond = double(frequencyCount.QuadPart);

    QueryPerformanceCounter(&frequencyCount);
    m_counterStart = frequencyCount.QuadPart;
}

float App::GetTime()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    return float(currentTime.QuadPart - m_counterStart) / m_countsPerSecond;
}

float App::GetFrameTime()
{
    LARGE_INTEGER currentTime;
    __int64 tickCount;
    QueryPerformanceCounter(&currentTime);

    tickCount = currentTime.QuadPart - m_frameTimeOld;
    m_frameTimeOld = currentTime.QuadPart;

    if (tickCount < 0.0f)
        tickCount = 0.0f;

    return float(tickCount) / m_countsPerSecond;
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