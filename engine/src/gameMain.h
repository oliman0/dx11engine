// gameMain.h
// Handles Game Logic and Update

#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

class Game
{
public:
	Game();
	~Game();

	void OnStart();
	void OnUpdate();
	void OnFixedUpdate();

	void Draw();

private:

};

