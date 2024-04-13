#pragma once

#include "rigidbody.h"
#include "collider.h"
#include "camera.h"

class Player : Camera
{
public:
	Player(Math::Vector3 startPosition);
	~Player();
	
	void UpdatePhysics(float deltaTime);
	bool TestCollision(Physics::AABBCollider& other, Math::Vector3 otherPosition);

	Physics::RigidBody* RigidBody();

	Math::Vector3 GetPosition();
	void MoveToPosition(Math::Vector3 position);
	void MoveByVector(Math::Vector3 vector);

	void SetCameraPitch(float pitch);
	void SetCameraYaw(float yaw);
	void AddCameraPitch(float pitch);
	void AddCameraYaw(float yaw);

	Math::Vector3 GetCameraFrontVector();
	Math::Vector3 GetCameraUpVector();

	DirectX::XMMATRIX CameraView();

private:
	Physics::RigidBody m_rigidBody;
	Physics::AABBCollider m_collider;
};

