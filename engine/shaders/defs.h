#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

struct Vertex
{
    Vertex() {}
    Vertex(float x, float y, float z,
        float u, float v)
        : pos(x, y, z), texCoord(u, v) {}

    XMFLOAT3 pos;
    XMFLOAT2 texCoord;
};

D3D11_INPUT_ELEMENT_DESC layout[] =
{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

struct cbPerObject
{
	XMMATRIX  WVP;
};