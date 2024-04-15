// engine_state.h
// A struct to store pointers to main systems that need be passed to update loops etc

#pragma once

#include "./d3d.h"
#include "./window.h"
#include "./timer.h"

struct EngineState {
	EngineState(Direct3D* d3d, Window* win, Time* time) :
		direct3d(d3d), window(win), engineTime(time)
	{}

	Direct3D* direct3d;
	Window* window;
	Time* engineTime;
};