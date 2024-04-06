#pragma once

#include <windows.h>

#define WINDOWSTYLE (WS_OVERLAPPED     | \
                     WS_CAPTION        | \
                     WS_SYSMENU        | \
                     WS_MINIMIZEBOX    | \
                     WS_MAXIMIZEBOX)

class Window
{
public:
	Window();
	~Window();

	HWND HWindow();

	void Close();
	
	bool ShouldClose();

	bool KeyDown(unsigned int key);
	bool KeyHold(unsigned int key);

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

	void PollEvents();

private:
	// Input
	bool m_keysDown[256];
	bool m_keysHold[256];

	HINSTANCE m_hInstance;
	LPCWSTR m_className;
	HWND m_hWnd;

	bool m_shouldClose;
};

static Window* WindowHandle = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);