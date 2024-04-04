// app.h
// Main Class of the Application
// Handles Windows and Input

#pragma once

#ifndef UNICODE
#define UNICODE
#endif UNICODE

#include <windows.h>
#include <d3d11.h>

#include "./d3d.h"
#include "./gameMain.h"
#include "../shaders/defs.h"
#include "./vertex_shader.h"
#include "./pixel_shader.h"
#include "./model.h"
#include "./cbuffer.h"

class App
{
public:
	App();
	~App();

	bool Initialize();
	void Run();
	void Shutdown();

	bool KeyDown(unsigned int key);
	bool KeyHold(unsigned int key);

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	void PollEvents();

private:
	Game* m_main;
	Direct3D* m_direct3d;

	// Input
	bool m_keysDown[256];
	bool m_keysHold[256];

	HINSTANCE m_hInstance;
	LPCWSTR m_className;
	HWND m_hWnd;
};

static App* ApplicationHandle = 0;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);