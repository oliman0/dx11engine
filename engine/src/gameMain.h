// gameMain.h
// Handles Game Logic and Update

#pragma once

#include <vector>

#include "../shaders/defs.h"
#include "./vertex_shader.h"
#include "./pixel_shader.h"
#include "./model.h"
#include "./cbuffer.h"
#include "./player.h"
#include "./engine_state.h"

#include "./engine_math.h"

struct Vertex
{
	Vertex() : pos(0, 0, 0), texCoord(0, 0) {}
	Vertex(float x, float y, float z,
		float u, float v)
		: pos(x, y, z), texCoord(u, v) {}

	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
};

static D3D11_INPUT_ELEMENT_DESC layout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

struct cbPerObject
{
	XMMATRIX  WVP;
};

/////////////////////////////////////////////////////////////////////////////////////////////

class Game
{
public:
	Game(EngineState engineState);
	~Game();

	void OnStart();
	void OnUpdate(EngineState engineState);
	void OnFixedUpdate(EngineState engineState);

	void Draw(Direct3D* direct3d);

private:
	XMMATRIX projection;
	Player player;

	std::vector<Model> models;

	VertexShader vertexShader;
	PixelShader pixelShader;
	ConstantBuffer mvpMatrixBuffer;

	Physics::AABBCollider floorCollider;
};

