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
	void StartTimer();
	float GetTime();
	float GetFrameTime();

private:
	Game* m_main;
	Direct3D* m_direct3d;
	Window* m_window;

	float m_countsPerSecond = 0.0;
	__int64 m_counterStart = 0;

	int m_frameCount = 0;
	int m_fps = 0;

	__int64 m_frameTimeOld = 0;
	float m_frameTime;
};