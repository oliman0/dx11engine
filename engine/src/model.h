// model.h
// 3D Model Class 

#pragma once

#include <d3d11.h>

#include <DirectXMath.h>
using namespace DirectX;

#include "./messager.h"
#include "./texture.h"

class Model
{
public:
	Model(ID3D11Device* device, ID3D11DeviceContext* deviceContext, UINT singleVertexSize, UINT vertexCount, void* vertices, UINT indexCount, DWORD* indices, LPCWSTR texturePath);
	~Model();

	void Draw();

	void Delete();

private:
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	UINT m_vertexCount, m_indexCount;
	UINT m_stride, m_offset;

	Texture* m_texture;

	ID3D11DeviceContext* m_deviceContext;
};

