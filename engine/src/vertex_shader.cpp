#include "vertex_shader.h"

VertexShader::VertexShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, UINT numOfElements, const D3D11_INPUT_ELEMENT_DESC* vertexDesc, const WCHAR* scrFilePath) : Shader(device, deviceContext), m_vertexShader(0) {
	ID3DBlob* vsBlob = nullptr;

	// Compile Shader
	bool comp = false;
	while (!comp) comp = CompileShader(scrFilePath, "VSMain", "vs_5_0", &vsBlob);

	// Create Input Layout
	HRESULT result = device->CreateInputLayout(vertexDesc, numOfElements, 
								vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_inputLayout);
	if (FAILED(result)) {
		ShowErrorBoxRepeat(L"Failed to create Vertex Input Layout.", L"Vertex Shader Error");
	}

	// Create Shader
	result = device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result)) {
		ShowErrorBoxRepeat(L"Failed to Create Vertex Shader.", L"Vertex Shader Error");
	}

	vsBlob->Release();
}

VertexShader::~VertexShader() {}

void VertexShader::Set() {
	// Bind the Input Layout
	m_deviceContext->IASetInputLayout(m_inputLayout);

	// Set as Active Shader
	m_deviceContext->VSSetShader(m_vertexShader, NULL, 0);
}

void VertexShader::Delete() {
	// Release DX Vertex Shader Object
	if (m_vertexShader) {
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
}