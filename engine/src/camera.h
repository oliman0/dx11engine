// camera.h
// Handles Virtual Camera and View Matrix

#pragma once

#include "engine_math.h"

class Camera
{
public:
	Camera(Math::Vector3 startPosition);
	~Camera();

	Math::Vector3 GetPosition();
	void MoveToPosition(Math::Vector3 position);
	void MoveByVector(Math::Vector3 vector);

	void SetPitch(float pitch);
	void SetYaw(float yaw);
	void AddPitch(float pitch);
	void AddYaw(float yaw);

	Math::Vector3 GetFrontVector();
	Math::Vector3 GetUpVector();

	DirectX::XMMATRIX View();

protected:
	Math::Vector3 m_position;
	Math::Vector3 m_up;
	Math::Vector3 m_forward;

	float m_pitch;
	float m_yaw;
};

