// cbuffer.h
// Class to handle Constant Buffers

#pragma once

#include <d3d11.h>

#include "./messager.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	ConstantBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, UINT bufferNumber, UINT size, void* data);
	~ConstantBuffer();

	void Update(ID3D11DeviceContext* deviceContext, void* data);
	
	void Set();

	void Delete();

private:
	ID3D11DeviceContext* m_deviceContext;
	ID3D11Buffer* m_constantBuffer;
	UINT m_bufferNum;
};

