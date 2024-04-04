#pragma once

#include <d3d11.h>
#include "../dependencies/WICTextureLoader11.h"
using namespace DirectX;

#include "./messager.h"

class Texture
{
public:
	Texture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, LPCWSTR texturePath);
	Texture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, LPCWSTR texturePath, unsigned int cpuAccessFlags, unsigned int miscFlags, WIC_LOADER_FLAGS loaderFlags);
	~Texture();

	void Set();

	void Delete();

private:
	ID3D11DeviceContext* m_deviceContext;

	ID3D11ShaderResourceView* m_texture;
	ID3D11SamplerState* m_samplerState;
};

