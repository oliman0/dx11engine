// gameMain.h
// Handles Game Logic and Update

#pragma once

#include <vector>

#include "../shaders/defs.h"
#include "./vertex_shader.h"
#include "./pixel_shader.h"
#include "./model.h"
#include "./cbuffer.h"
#include "./camera.h"
#include "./engine_state.h"

struct Vertex
{
	Vertex() {}
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
	void OnFixedUpdate();

	void Draw(Direct3D* direct3d);

private:
	XMMATRIX projection;
	Camera camera;

	std::vector<Model> models;

	VertexShader vertexShader;
	PixelShader pixelShader;
	ConstantBuffer wvpMatrixBuffer;
};

