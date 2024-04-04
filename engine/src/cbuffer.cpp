#include "cbuffer.h"

ConstantBuffer::ConstantBuffer() : m_constantBuffer(0), m_bufferNum(0) {}

ConstantBuffer::ConstantBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, UINT bufferNumber, UINT size, void* data) : m_bufferNum(bufferNumber), m_deviceContext(deviceContext) {
	// Fill in a buffer description.
	D3D11_BUFFER_DESC cbDesc;
	ZeroMemory(&cbDesc, sizeof(D3D11_BUFFER_DESC));

	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.ByteWidth = size;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;

	// Fill in the subresource data.
	D3D11_SUBRESOURCE_DATA initData;
	initData.pSysMem = data;

	// Create the Buffer
	HRESULT hr = device->CreateBuffer(&cbDesc, &initData, &m_constantBuffer);
	// If failed show an error MessageBox
	if (FAILED(hr)) GlobalMessager->ShowErrorBoxRepeat(L"Failed to create CBuffer", L"CBuffer Error");
}

ConstantBuffer::~ConstantBuffer() {}

void ConstantBuffer::Update(ID3D11DeviceContext* deviceContext, void* data) {
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	// Lock the cbuffer so the gpu cannot write to it
	HRESULT hr = deviceContext->Map(m_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr)) GlobalMessager->ShowErrorBoxRepeat(L"Failed to map CBuffer", L"CBuffer Error");

	// Set the data
	mappedResource.pData = data;

	// Unlock the cbuffer
	deviceContext->Unmap(m_constantBuffer, 0);
}

void ConstantBuffer::Set() {
	// Set the constant buffer
	m_deviceContext->VSSetConstantBuffers(m_bufferNum, 1, &m_constantBuffer);
}

void ConstantBuffer::Delete() {
	// Release the dx cbuffer object
	if (m_constantBuffer) {
		m_constantBuffer->Release();
		m_constantBuffer = 0;
	}
}