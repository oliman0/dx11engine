// camera.h
// Handles Virtual Camera and View Matrix

#pragma once

#include <DirectXMath.h>
using namespace DirectX;

class Camera
{
public:
	Camera(XMVECTOR startPosition);
	~Camera();

	void MoveToPosition(XMVECTOR position);
	void MoveByVector(XMVECTOR vector);

	XMMATRIX View();

private:
	XMVECTOR m_position;
	XMVECTOR m_up;
	XMVECTOR m_forward;
};

