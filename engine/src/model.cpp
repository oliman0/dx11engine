#include "model.h"

Model::Model(ID3D11Device* device, ID3D11DeviceContext* deviceContext, UINT singleVertexSize, UINT vertexCount, void* vertices, UINT indexCount, DWORD* indices, LPCWSTR texturePath) :
    m_stride(singleVertexSize), m_offset(0), m_vertexCount(vertexCount), m_indexCount(indexCount), m_vertexBuffer(0), m_indexBuffer(0), m_deviceContext(deviceContext), m_texture(0)
{
    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

    // Set Buffer Description
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = singleVertexSize * vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexBufferData;

    // Set Buffer Data
    ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
    vertexBufferData.pSysMem = vertices;

    // Create Buffer
    HRESULT hr = device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_vertexBuffer);
    if (FAILED(hr)) GetMessager()->ShowErrorBoxRepeat(L"Failed to Create Vertex Buffer.", L"Error");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    D3D11_BUFFER_DESC indexBufferDesc;
    ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

    // Set Buffer Description
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(DWORD) * indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA indexBufferData;

    // Set Buffer Data
    ZeroMemory(&indexBufferData, sizeof(indexBufferData));
    indexBufferData.pSysMem = indices;

    // Create Buffer
    hr = device->CreateBuffer(&indexBufferDesc, &indexBufferData, &m_indexBuffer);
    if (FAILED(hr)) GetMessager()->ShowErrorBoxRepeat(L"Failed to Create Index Buffer.", L"Error");

    // Create Texture
    m_texture = new Texture(device, deviceContext, texturePath);
}

Model::~Model() {}

void Model::Draw() {
    // Set Vertex Buffer
    m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &m_stride, &m_offset);
    // Set Index Buffer
    m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, m_offset);

    // Set the texture
    if (m_texture) m_texture->Set();

    // Set Primitive Topology
    m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Draw
    m_deviceContext->DrawIndexed(m_indexCount, 0, 0);
}

void Model::Delete() {
    if (m_vertexBuffer) {
        m_vertexBuffer->Release();
        m_vertexBuffer = 0;
    }

    if (m_indexBuffer) {
        m_indexBuffer->Release();
        m_indexBuffer = 0;
    }

    if (m_texture) {
        m_texture->Delete();
        m_texture = 0;
    }
}