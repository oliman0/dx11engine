// player.h
// Similar to physics_object.h but handles specifically the player and camera.

#pragma once

#include "rigidbody.h"
#include "collider.h"
#include "camera.h"

class Player : public Physics::RigidBody, Camera
{
public:
	Player(Math::Vector3 startPosition);
	~Player();
	
	Math::Vector3 GetPosition();
	void SetPosition(Math::Vector3 position);
	void MoveByVector(Math::Vector3 vector);

	void Update(Time* time);

	void TestCollision(Physics::AABBCollider& other, Math::Vector3 otherPosition);

	void SetCameraPitch(float pitch);
	void SetCameraYaw(float yaw);
	void AddCameraPitch(float pitch);
	void AddCameraYaw(float yaw);

	Math::Vector3 GetCameraFrontVector();
	Math::Vector3 GetCameraUpVector();

	DirectX::XMMATRIX CameraView();

private:
	Physics::AABBCollider m_collider;
	Physics::AABBCollider m_groundedCollider;
};

