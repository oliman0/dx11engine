// app.h
// Main Class of the Application
// Handles Windows and Input

#pragma once

#ifndef UNICODE
#define UNICODE
#endif UNICODE

#include <d3d11.h>

#include "./gameMain.h"
#include "./engine_state.h"

class App
{
public:
	App();
	~App();

	bool Initialize();
	void Run();
	void Shutdown();

private:
	void GetCounterFrequency();
	void CalculateDeltaTime();

private:
	Game* m_main;
	Direct3D* m_direct3d;
	Window* m_window;

	float m_countsPerSecond;

	__int64 m_lastTime;
	float m_deltaTime;
	float m_maxDeltaTime;
};