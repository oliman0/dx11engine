#include "gameMain.h"

Game::Game(EngineState engineState) :
	projection(XMMatrixPerspectiveFovLH(1.309f, 1920.0f / 1080.0f, 0.1f, 1000.0f)),
	player(Math::Vector3(0.0f, 100.0f, 0.0f)),
	vertexShader(engineState.direct3d->GetDevice(), engineState.direct3d->GetDeviceContext(), 2, layout, L"./shaders/vertex_shader.hlsl"),
	pixelShader(engineState.direct3d->GetDevice(), engineState.direct3d->GetDeviceContext(), L"./shaders/pixel_shader.hlsl"),
	mvpMatrixBuffer(engineState.direct3d->GetDevice(), engineState.direct3d->GetDeviceContext(), 0, sizeof(cbPerObject)),
    floorCollider(Math::Vector3(-50.0f, -5.0f, -50.0f), Math::Vector3(50.0f, 0.0f, 50.0f)),
    wallCollider(Math::Vector3(-50.0f, 0.0f, -51.0f), Math::Vector3(50.0f, 10.0f, -50.0f))
{
    //Create the vertex buffer
    Vertex v[] =
    {
        // Front Face
        Vertex(-1.0f, -1.0f, -2.0f, 0.0f, 1.0f),
        Vertex(-1.0f,  1.0f, -2.0f, 0.0f, 0.0f),
        Vertex(1.0f,  1.0f, -2.0f, 1.0f, 0.0f),
        Vertex(1.0f, -1.0f, -2.0f, 1.0f, 1.0f),

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

    Vertex v2[] = {
        Vertex(-50.0f, 0.0f, -50.0f, 0.0f, 10.0f),
        Vertex(-50.0f, 0.0f,  50.0f, 0.0f, 0.0f),
        Vertex(50.0f, 0.0f,  50.0f, 10.0f, 0.0f),
        Vertex(50.0f, 0.0f, -50.0f, 10.0f, 10.0f),
    };

    DWORD i2[] = {
        0,  1,  2,
        0,  2,  3,
    };

    models.push_back(Model(engineState.direct3d->GetDevice(), engineState.direct3d->GetDeviceContext(), sizeof(Vertex), 4, v2, 6, i2, L"./res/textures/grey_bordered_fill.png"));
}

Game::~Game() {
    vertexShader.Delete();
    pixelShader.Delete();
    mvpMatrixBuffer.Delete();

    for (auto& m : models) m.Delete();
}

void Game::OnStart() {}

void Game::OnUpdate(EngineState engineState, float deltaTime) {
    Math::Vector3 front = player.GetCameraFrontVector();
    front.y = 0.0f;

    Math::Vector3 up = player.GetCameraUpVector();

    Math::Vector3 movement(0.0f);

    if (engineState.window->KeyHold(0x53)) movement += -front;
    if (engineState.window->KeyHold(0x57)) movement += front;
    if (engineState.window->KeyHold(0x44)) movement += -Math::Normalize(Math::Cross(front, up));
    if (engineState.window->KeyHold(0x41)) movement += Math::Normalize(Math::Cross(front, up));

    movement = Math::Normalize(movement) * 50 * deltaTime;
    player.MoveByVector(movement);

    if (engineState.window->KeyDown(VK_SPACE) && player.RigidBody()->GetGrounded()) {
        player.RigidBody()->AddForce(Math::Vector3(0.0f, 50000.0f, 0.0f)); }

    player.UpdatePhysics(deltaTime);

    player.TestCollision(floorCollider, Math::Vector3(0.0f));
    //player.TestCollision(wallCollider, Math::Vector3(0.0f));

    if (engineState.window->KeyDown(VK_F1)) engineState.window->SetCursorLocked(!engineState.window->GetCursorLocked());

    Math::Vector2 mouse = engineState.window->GetMouseOffset();
    player.AddCameraPitch(-mouse.y * 50.0f *  deltaTime);
    player.AddCameraYaw(-mouse.x * 50.0f * deltaTime);

    cbPerObject cbPerObj;
    cbPerObj.WVP = XMMatrixTranspose(player.CameraView() * projection);

    mvpMatrixBuffer.UpdateData(&cbPerObj);
}

void Game::OnFixedUpdate() {}

void Game::Draw(Direct3D* direct3d) {
    vertexShader.Set();
    pixelShader.Set();
    mvpMatrixBuffer.Set();

    direct3d->SetViewport();

    direct3d->ClearColourAndDepth(0.1f, 0.1f, 0.1f, 0.0f);

    for (auto& m : models) m.Draw();

    direct3d->Present();
}