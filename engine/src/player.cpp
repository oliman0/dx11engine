#include "player.h"

Player::Player(Math::Vector3 startPosition) : Camera(startPosition), RigidBody(startPosition, 1.0f, Math::Vector3(0.0f, -100.0f, 0.0f), 0.85f), m_collider(Math::Vector3(-1.0f, -2.5f, -1.0f), Math::Vector3(1.0f, 0.0f, 1.0f)), m_groundedCollider(Math::Vector3(-1.0f, -2.6f, -1.0f), Math::Vector3(1.0f, -2.4f, 1.0f)) {}
Player::~Player() {}

Math::Vector3 Player::GetPosition() { return RigidBody::GetPosition(); }
void Player::SetPosition(Math::Vector3 position) { RigidBody::SetPosition(position); }
void Player::MoveByVector(Math::Vector3 vector) { RigidBody::MoveByVector(vector); }

void Player::Update(PhysicsWorld* physicsWorld, Time* time) {
	m_position = GetInterpolatedPosition(time);

	std::vector<Physics::Collision> collisions = physicsWorld->TestCollision(m_collider, m_position);
	for (auto& collision : collisions) m_physicsPosition += collision.normal * collision.depth;

	if (physicsWorld->TestCollisionSingle(m_groundedCollider, m_position)) {
		if (m_velocity.y < 0.0f) m_grounded = true;
	}
	else m_grounded = false;
}

void Player::SetCameraPitch(float pitch) { Camera::SetPitch(pitch); }
void Player::SetCameraYaw(float yaw) { Camera::SetYaw(yaw); }
void Player::AddCameraPitch(float pitch) { Camera::AddPitch(pitch); }
void Player::AddCameraYaw(float yaw) { Camera::AddYaw(yaw); }

Math::Vector3 Player::GetCameraFrontVector() { return Camera::GetFrontVector(); }
Math::Vector3 Player::GetCameraUpVector() { return Camera::GetUpVector(); }

DirectX::XMMATRIX Player::CameraView() { return Camera::View(); }