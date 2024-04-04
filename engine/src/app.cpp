#include "app.h"

App::App() : m_className(L""), m_direct3d(0), m_hInstance(0), m_hWnd(0), m_main(0) {
    for (int i = 0; i < 256; i++)
    {
        m_keysDown[i] = false;
    }
    for (int i = 0; i < 256; i++)
    {
        m_keysHold[i] = false;
    }
}

App::~App() {}

bool App::Initialize() {
    // Register the window class.
    m_className = L"Engine Class";

    ApplicationHandle = this;

    WNDCLASS wc = { };

    m_hInstance = GetModuleHandle(NULL);

    wc.lpfnWndProc = WindowProc;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = m_hInstance;
    wc.lpszClassName = m_className;
    wc.hIcon = ExtractIcon(m_hInstance, L"./icon.ico", 0);

    RegisterClass(&wc);

    // Create the window.

    m_hWnd = CreateWindowEx(
        0,                                // Optional window styles.
        m_className,                     // Window class
        L"Directx 11",                  // Window text
        WS_OVERLAPPEDWINDOW,           // Window style

        // Size and position
        0, 0, 1920, 1080,

        NULL,           // Parent window    
        NULL,          // Menu
        m_hInstance,  // Instance handle
        NULL         // Additional application data
    );

    if (m_hWnd == NULL)
    {
        return false;
    }

    ShowWindow(m_hWnd, TRUE);

    m_direct3d = new Direct3D;
    m_direct3d->Initialize(1920, 1080, true, m_hWnd, false, 100.0f, 0.1f);

    m_main = new Game;

    return true;
}

void App::PollEvents() {
    for (int i = 0; i < 256; i++)
    {
        m_keysDown[i] = false;
    }

    MSG msg = { };
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) Shutdown();

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void App::Run() {
    //Compile Shaders from shader file
    VertexShader VS(m_direct3d->GetDevice(), m_direct3d->GetDeviceContext(), 2, layout, L"./shaders/vertex_shader.hlsl");
    PixelShader PS(m_direct3d->GetDevice(), m_direct3d->GetDeviceContext(), L"./shaders/pixel_shader.hlsl");

    //Set Vertex and Pixel Shaders
    VS.Set();
    PS.Set();

    //Create the vertex buffer
    Vertex v[] =
    {
        // Front Face
        Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
        Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
        Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

        // Back Face
        Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
        Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
        Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),

        // Top Face
        Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
        Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
        Vertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f),
        Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

        // Bottom Face
        Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
        Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Vertex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f),
        Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f),

        // Left Face
        Vertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f),
        Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f),
        Vertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
        Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

        // Right Face
        Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
        Vertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f),
        Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f),
    };

    DWORD i[] = {
        // Front Face
        0,  1,  2,
        0,  2,  3,

        // Back Face
        4,  5,  6,
        4,  6,  7,

        // Top Face
        8,  9, 10,
        8, 10, 11,

        // Bottom Face
        12, 13, 14,
        12, 14, 15,

        // Left Face
        16, 17, 18,
        16, 18, 19,

        // Right Face
        20, 21, 22,
        20, 22, 23
    };

    Model m(m_direct3d->GetDevice(), m_direct3d->GetDeviceContext(), sizeof(Vertex), 24, v, 36, i, L"./res/textures/largecheck.png");

    XMVECTOR camPosition = XMVectorSet(5.0f, 2.0f, -10.0f, 0.0f);
    XMVECTOR camTarget = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
    XMVECTOR camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    XMMATRIX view = XMMatrixLookAtLH(camPosition, camTarget, camUp);
    XMMATRIX proj = XMMatrixPerspectiveFovLH(1.309f, 1920.0f / 1080.0f, 0.1f, 1000.0f);
    XMMATRIX wvp = XMMatrixIdentity() * view * proj;

    cbPerObject cbPerObj;
    cbPerObj.WVP = XMMatrixTranspose(wvp);

    ConstantBuffer cb(m_direct3d->GetDevice(), m_direct3d->GetDeviceContext(), 0, sizeof(cbPerObj), &cbPerObj);
    cb.Set();

    m_direct3d->SetViewport();
    
    while (true) {
        // Process Events
        PollEvents();
        if (KeyDown(VK_ESCAPE)) break;
        
        //Run Draw Loop

        m_direct3d->ClearColourAndDepth(0.0f, 0.0f, 0.0f, 0.0f);

        m.Draw();

        m_direct3d->Present();
        
    }
}

void App::Shutdown() {
    m_direct3d->Shutdown();

    // Remove the window.
    DestroyWindow(m_hWnd);
    m_hWnd = NULL;

    // Remove the application instance.
    UnregisterClass(m_className, m_hInstance);
    m_hInstance = NULL;

    ApplicationHandle = 0;
}

bool App::KeyDown(unsigned int key) { return m_keysDown[key]; }
bool App::KeyHold(unsigned int key) { return m_keysHold[key]; }

LRESULT CALLBACK App::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    switch (umsg)
    {
        // Check if a key has been pressed on the keyboard.
    case WM_KEYDOWN:
    {
        // If a key is pressed send it to the input object so it can record that state.
        m_keysDown[(unsigned int)wparam] = true;
        m_keysHold[(unsigned int)wparam] = true;
        return 0;
    }

    // Check if a key has been released on the keyboard.
    case WM_KEYUP:
    {
        // If a key is released then send it to the input object so it can unset the state for that key.
        m_keysHold[(unsigned int)wparam] = false;
        return 0;
    }

    // Any other messages send to the default message handler as our application won't make use of them.
    default:
    {
        return DefWindowProc(hwnd, umsg, wparam, lparam);
    }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE _hPrevInstance, PWSTR _pCmdLine, int _nCmdShow) {
    App app;

    if (app.Initialize()) {
        app.Run();
    }

    app.Shutdown();

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    default:
    {
        return ApplicationHandle->MessageHandler(hwnd, uMsg, wParam, lParam);
    }

    }
}