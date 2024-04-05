#pragma once

#include "./d3d.h"
#include "./window.h"

struct EngineState {
	EngineState(Direct3D* d3d, Window* win) :
		direct3d(d3d), window(win)
	{}

	Direct3D* direct3d;
	Window* window;
};