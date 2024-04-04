// pixel_shader.h
// Class that manages the Pixel Shader

#pragma once

#include "shader.h"

class PixelShader : Shader
{
public:
	PixelShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* scrFilePath);
	~PixelShader();

	virtual void Set();

	virtual void Delete();

private:
	ID3D11PixelShader* m_pixelShader;
};

