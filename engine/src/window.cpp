#include "window.h"

Window::Window(int windowWidth, int windowHeight, LPCWSTR title, bool showConsole) : m_className(L""), m_hInstance(0), m_hWnd(0), m_shouldClose(false), m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_cursorLocked(false),
                                                                                     m_mousePosition(0, 0), m_mouseOffset(0, 0) {
    for (int i = 0; i < 256; i++)
    {
        m_keysDown[i] = false;
    }
    for (int i = 0; i < 256; i++)
    {
        m_keysHold[i] = false;
    }

    // Register the window class.
    m_className = L"Engine Class";

    WindowHandle = this;

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
        title,                          // Window text
        WINDOWSTYLE,                   // Window style

        // Size and position
        0, 0, windowWidth, windowHeight,

        NULL,           // Parent window    
        NULL,          // Menu
        m_hInstance,  // Instance handle
        NULL         // Additional application data
    );

    if (m_hWnd == NULL)
    {
        //return false;
    }

    ShowWindow(m_hWnd, TRUE);

    if (showConsole) {
        AllocConsole();
        FILE* fDummy;
        freopen_s(&fDummy, "CONOUT$", "w", stdout);
    }
}

Window::~Window() {}

HWND Window::GetHWindow() { return m_hWnd; }

void Window::Close() {
    // Remove the window.
    DestroyWindow(m_hWnd);
    m_hWnd = NULL;

    // Remove the application instance.
    UnregisterClass(m_className, m_hInstance);
    m_hInstance = NULL;

    WindowHandle = 0;

    m_shouldClose = true;
}

bool Window::ShouldClose() { return m_shouldClose; }

LRESULT CALLBACK Window::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
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
    case WM_MOUSEMOVE:
    {
        if (m_cursorLocked) {
            POINT pos;
            GetCursorPos(&pos);

            m_mouseOffset = Math::Vector2((float)pos.x - ((float)m_windowWidth / 2.0f), (float)pos.y - ((float)m_windowHeight / 2.0f));

            m_mousePosition = Math::Vector2((float)pos.x, (float)pos.y);

            if (GetFocus() == m_hWnd) SetCursorPos(m_windowWidth / 2, m_windowHeight / 2);
        }
        else {
            POINT pos;
            GetCursorPos(&pos);

            m_mouseOffset = Math::Vector2((float)pos.x - (float)m_mousePosition.x, (float)pos.y - (float)m_mousePosition.y);

            m_mousePosition = Math::Vector2((float)pos.x, (float)pos.y);
        }
    }

    // Any other messages send to the default message handler as our application won't make use of them.
    default:
    {
        return DefWindowProc(hwnd, umsg, wparam, lparam);
    }
    }
}

void Window::PollEvents() {
    for (int i = 0; i < 256; i++)
    {
        m_keysDown[i] = false;
    }

    MSG msg = { };
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) Close();

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

bool Window::KeyDown(unsigned int key) { return m_keysDown[key]; }
bool Window::KeyHold(unsigned int key) { return m_keysHold[key]; }

Math::Vector2 Window::GetMousePosition() { return m_mousePosition; }
Math::Vector2 Window::GetMouseOffset() { return m_mouseOffset; }

void Window::SetCursorLocked(bool lock) { m_cursorLocked = lock; ShowCursor(!lock); }
bool Window::GetCursorLocked() { return m_cursorLocked; }

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
        return WindowHandle->MessageHandler(hwnd, uMsg, wParam, lParam);
    }

    }
}