// vertex_shader.h
// Class that manages the Vertex Shader

#pragma once

#include <string>

#include "shader.h"

class VertexShader : Shader
{
public:
	VertexShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, UINT numOfElements, const D3D11_INPUT_ELEMENT_DESC* vertexDesc, const WCHAR* scrFilePath);
	~VertexShader();

	virtual void Set();

	virtual void Delete();

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11InputLayout* m_inputLayout;
};

