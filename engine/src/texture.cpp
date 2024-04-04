#include "texture.h"

Texture::Texture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, LPCWSTR texturePath, unsigned int cpuAccessFlags, unsigned int miscFlags, WIC_LOADER_FLAGS loaderFlags) : m_texture(0), m_samplerState(0), m_deviceContext(deviceContext) {
	// Describe Sampler State
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));

	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create Sampler State
	HRESULT hr = device->CreateSamplerState(&sampDesc, &m_samplerState);
	if (FAILED(hr)) GlobalMessager->ShowErrorBoxRepeat(L"Failed to Create Texture Sampler State", L"Error");

	// Load Texture
	hr = CreateWICTextureFromFileEx(device, deviceContext, texturePath, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, WIC_LOADER_IGNORE_SRGB, nullptr, &m_texture);
	if(FAILED(hr)) GlobalMessager->ShowErrorBoxRepeat(L"Failed to Load Texture", L"Error");
}

Texture::Texture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, LPCWSTR texturePath) : Texture(device, deviceContext, texturePath, 0, 0, WIC_LOADER_IGNORE_SRGB) {}

Texture::~Texture() {}

void Texture::Set() {
	m_deviceContext->PSSetShaderResources(0, 1, &m_texture);
	m_deviceContext->PSSetSamplers(0, 1, &m_samplerState);
}

void Texture::Delete() {
	if (m_texture) {
		m_texture->Release();
		m_texture = 0;
	}

	if (m_samplerState) {
		m_samplerState->Release();
		m_samplerState = 0;
	}
}