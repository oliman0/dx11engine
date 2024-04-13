// shader.h
// Base shader class

#pragma once

#include <fstream>

#include <d3d11.h>
#include <d3dcompiler.h>

#include "./messager.h"
#include "./cbuffer.h"

class Shader {
public:
	Shader(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	~Shader();

	virtual void Set() = 0;

	virtual void Delete() = 0;

protected:
	bool CompileShader(const WCHAR* scrFilePath, const char* entryPoint, const char* profile, ID3DBlob** blob);

protected:
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
};

