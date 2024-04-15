// app.h
// Main Class of the Application 

#pragma once

#ifndef UNICODE
#define UNICODE
#endif UNICODE

#include <d3d11.h>

#include "./gameMain.h"
#include "./engine_state.h"
#include "./timer.h"

class App
{
public:
	App();
	~App();

	bool Initialize();
	void Run();
	void Shutdown();

private:
	Game* m_main;
	Direct3D* m_direct3d;
	Window* m_window;
	Time* m_engineTimer;
};