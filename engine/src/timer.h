// timer.h
// Handles Timers, Calculating Time Deltas and the Tick System (FixedUpdate)

#pragma once

#include <windows.h>

typedef __int64 TIMER;

class Time
{
public:
	Time(float maxDeltaTime, int tickRate);
	~Time();

	TIMER StartTimer();
	float GetTimerTime(TIMER timer);
	void ResetTimer(TIMER& timer);

	bool Tick();

	float FrameDelta();
	float TickDelta();

	int GetTickRate();
	TIMER GetTickTimer();

private:
	float GetCounterFrequency();
	__int64 GetCount();

private:
	TIMER m_tickTimer;
	int m_tickRate;
	float m_tickDelta;

	TIMER m_frameTimer;
	float m_frameDelta;
	float m_maxFrameDelta;

	float m_countsPerSecond;
};

