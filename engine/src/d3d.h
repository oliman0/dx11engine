// D3D.h
// The Class that handles Direct3D.

#pragma once

// Linking
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma warning(suppress : 6387)

#include <d3d11.h>

class Direct3D
{
public:
    Direct3D();
    ~Direct3D();

    bool Initialize(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
    void Shutdown();

    void ClearColourAndDepth(float red, float green, float blue, float alpha);
    void ClearColour(float red, float green, float blue, float alpha);
    void ClearDepth();
    void Present();

    ID3D11Device* GetDevice();
    ID3D11DeviceContext* GetDeviceContext();

    void SetViewport();

    void GetVideoCardInfo(char* cardName, int& memory);

private:
    bool m_vsyncEnabled;
    int m_videoCardMemory;
    char m_videoCardDescription[128];
    IDXGISwapChain* m_swapChain;
    ID3D11Device* m_device;
    ID3D11DeviceContext* m_deviceContext;
    ID3D11RenderTargetView* m_renderTargetView;
    D3D11_VIEWPORT m_viewport;
    ID3D11DepthStencilView* m_depthStencilView;
    ID3D11Texture2D* m_depthStencilBuffer;
    ID3D11RasterizerState* m_rasterState;
};

