#include "timer.h"

Time::Time(float maxDeltaTime, int tickRate) : m_countsPerSecond(0), m_maxFrameDelta(maxDeltaTime), m_tickTimer(0), m_tickRate(tickRate), m_frameTimer(0), m_tickDelta(0), m_frameDelta(0) {
    m_countsPerSecond = GetCounterFrequency();
    m_tickTimer = StartTimer();
    m_frameTimer = StartTimer();
}

Time::~Time() {}

// Timer Funcs

TIMER Time::StartTimer() { return GetCount(); }

float Time::GetTimerTime(TIMER timer) { return (GetCount() - timer) / m_countsPerSecond; }

void Time::ResetTimer(TIMER& timer) { timer = GetCount(); }

// Others

bool Time::Tick() { 
    m_frameDelta = GetTimerTime(m_frameTimer);
    if (m_frameDelta > m_maxFrameDelta) m_frameDelta = m_maxFrameDelta;
    ResetTimer(m_frameTimer);

    bool tick = GetTimerTime(m_tickTimer) >= 1.0f/m_tickRate;
    if (tick) {
        m_tickDelta = GetTimerTime(m_tickTimer);

        ResetTimer(m_tickTimer);
        return true;
    }

    return false;
}

float Time::FrameDelta() { return m_frameDelta; }
float Time::TickDelta() { return m_tickDelta; }

float Time::GetCounterFrequency() {
    LARGE_INTEGER frequencyCount;
    QueryPerformanceFrequency(&frequencyCount);

    return float(frequencyCount.QuadPart);
}

__int64 Time::GetCount() {
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);

    return currentTime.QuadPart;
}

int Time::GetTickRate() { return m_tickRate; }
TIMER Time::GetTickTimer() { return m_tickTimer; }