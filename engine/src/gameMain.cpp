#include "gameMain.h"

Game::Game(EngineState engineState) :
	projection(XMMatrixPerspectiveFovLH(1.309f, 1920.0f / 1080.0f, 0.1f, 1000.0f)),
	camera(XMVectorSet(2.0f, 1.5f, -5.0f, 0.0f)),
	vertexShader(engineState.direct3d->GetDevice(), engineState.direct3d->GetDeviceContext(), 2, layout, L"./shaders/vertex_shader.hlsl"),
	pixelShader(engineState.direct3d->GetDevice(), engineState.direct3d->GetDeviceContext(), L"./shaders/pixel_shader.hlsl"),
	wvpMatrixBuffer(engineState.direct3d->GetDevice(), engineState.direct3d->GetDeviceContext(), 0, sizeof(cbPerObject))
{
    //Create the vertex buffer
    Vertex v[] =
    {
        // Front Face
        Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
        Vertex(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
        Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

        // Back Face
        Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
        Vertex(1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
        Vertex(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),

        // Top Face
        Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
        Vertex(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
        Vertex(1.0f, 1.0f,  1.0f, 1.0f, 0.0f),
        Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

        // Bottom Face
        Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
        Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Vertex(1.0f, -1.0f,  1.0f, 0.0f, 0.0f),
        Vertex(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f),

        // Left Face
        Vertex(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f),
        Vertex(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f),
        Vertex(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
        Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

        // Right Face
        Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Vertex(1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
        Vertex(1.0f,  1.0f,  1.0f, 1.0f, 0.0f),
        Vertex(1.0f, -1.0f,  1.0f, 1.0f, 1.0f),
    };

    DWORD i[] = {
        // Front Face
        0,  1,  2,
        0,  2,  3,

        // Back Face
        4,  5,  6,
        4,  6,  7,

        // Top Face
        8,  9, 10,
        8, 10, 11,

        // Bottom Face
        12, 13, 14,
        12, 14, 15,

        // Left Face
        16, 17, 18,
        16, 18, 19,

        // Right Face
        20, 21, 22,
        20, 22, 23
    };

    models.push_back(Model(engineState.direct3d->GetDevice(), engineState.direct3d->GetDeviceContext(), sizeof(Vertex), 24, v, 36, i, L"./res/textures/largecheck.png"));
}

Game::~Game() {}

void Game::OnStart() {}

void Game::OnUpdate(EngineState engineState) {
    cbPerObject cbPerObj;
    cbPerObj.WVP = XMMatrixTranspose(camera.View() * projection);

    wvpMatrixBuffer.UpdateData(&cbPerObj);
}

void Game::OnFixedUpdate() {}

void Game::Draw(Direct3D* direct3d) {
    vertexShader.Set();
    pixelShader.Set();
    wvpMatrixBuffer.Set();

    direct3d->SetViewport();

    direct3d->ClearColourAndDepth(0.1f, 0.1f, 0.1f, 0.0f);

    for (auto m : models) m.Draw();

    direct3d->Present();
}