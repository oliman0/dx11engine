#include "player.h"

Player::Player(Math::Vector3 startPosition) : Camera(startPosition), RigidBody(startPosition, 1.0f, Math::Vector3(0.0f, -100.0f, 0.0f), 0.85f), m_collider(Math::Vector3(-1.0f, -2.5f, -1.0f), Math::Vector3(1.0f, 0.0f, 1.0f)), m_groundedCollider(Math::Vector3(-0.5f, -2.6f, 0.5f), Math::Vector3(0.5f, -2.4f, 0.5f)) {}
Player::~Player() {}

Math::Vector3 Player::GetPosition() { return RigidBody::GetPosition(); }
void Player::SetPosition(Math::Vector3 position) { RigidBody::SetPosition(position); }
void Player::MoveByVector(Math::Vector3 vector) { RigidBody::MoveByVector(vector); }

void Player::Update(Time* time) {
	m_position = GetInterpolatedPosition(time);
}

void Player::TestCollision(Physics::AABBCollider& other, Math::Vector3 otherPosition) {
	Physics::Collision c;

	if (m_collider.TestCollision(c, m_position, other, otherPosition)) {
		m_physicsPosition += c.normal * c.depth;
	}

	if (m_groundedCollider.TestCollision(m_position, other, otherPosition)) {
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