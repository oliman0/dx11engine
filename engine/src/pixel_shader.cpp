#include "pixel_shader.h"

PixelShader::PixelShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const WCHAR* scrFilePath) : Shader(device, deviceContext), m_pixelShader(0) {
	ID3DBlob* psBlob = nullptr;

	// Compile Shader
	bool comp = false;
	while (!comp) comp = CompileShader(scrFilePath, "PSMain", "ps_5_0", &psBlob);

	// Create Shader
	HRESULT result = device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result)) {
		ShowErrorBoxRepeat(L"Failed to Create Pixel Shader.", L"Pixel Shader Error");
	}

	psBlob->Release();
}

PixelShader::~PixelShader() {}

void PixelShader::Set() {
	// Set as Active Shader
	m_deviceContext->PSSetShader(m_pixelShader, NULL, 0);
}

void PixelShader::Delete() {
	// Release DX Shader Shader Object
	if (m_pixelShader) {
		m_pixelShader->Release();
		m_pixelShader = 0;
	}
}