#pragma once

#include <windows.h>
#include <iostream>

#include <string>

#include <DirectXMath.h>
using namespace DirectX;

#define WINDOWSTYLE (WS_OVERLAPPED     | \
                     WS_CAPTION        | \
                     WS_SYSMENU        | \
                     WS_MINIMIZEBOX    | \
                     WS_MAXIMIZEBOX)

class Window
{
public:
	Window(int windowWidth, int windowHeight, LPCWSTR title, bool showConsole = false);
	~Window();

	HWND GetHWindow();

	void Close();
	
	bool ShouldClose();

	bool KeyDown(unsigned int key);
	bool KeyHold(unsigned int key);

	XMFLOAT2 GetMousePosition();
	XMFLOAT2 GetMouseOffset();

	void SetCursorLocked(bool lock);
	bool GetCursorLocked();

	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

	void PollEvents();

private:
	int m_windowWidth, m_windowHeight;
	bool m_cursorLocked;

	// Input
	bool m_keysDown[256];
	bool m_keysHold[256];

	XMFLOAT2 m_mousePosition;
	XMFLOAT2 m_mouseOffset;

	HINSTANCE m_hInstance;
	LPCWSTR m_className;
	HWND m_hWnd;

	bool m_shouldClose;
};

static Window* WindowHandle = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);