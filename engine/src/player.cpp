#include "player.h"

Player::Player(Math::Vector3 startPosition) : Camera(startPosition), m_rigidBody(1.0f, Math::Vector3(0.0f, -50.0f, 0.0f)), m_collider(Math::Vector3(-1.0f, -2.5f, -1.0f), Math::Vector3(1.0f, 0.0f, 1.0f)) {}
Player::~Player() {}

bool Player::TestCollision(Physics::AABBCollider& other, Math::Vector3 otherPosition) { 
	Physics::Collision c;

	if (m_collider.TestCollision(c, m_position, other, otherPosition)) {
		if (c.normal.y == 1 && m_rigidBody.GetVelocity().y < 0.0f) m_rigidBody.SetGrounded(true);
		
		m_position += c.normal * c.depth;

		return true;
	}
	else if (m_rigidBody.GetGrounded()) m_rigidBody.SetGrounded(false);

	return false;
}

Physics::RigidBody* Player::RigidBody() { return &m_rigidBody; }

Math::Vector3 Player::GetPosition() { return Camera::GetPosition(); }
void Player::MoveToPosition(Math::Vector3 position) { Camera::MoveToPosition(position); }
void Player::MoveByVector(Math::Vector3 vector) { Camera::MoveByVector(vector); }

void Player::SetCameraPitch(float pitch) { Camera::SetPitch(pitch); }
void Player::SetCameraYaw(float yaw) { Camera::SetYaw(yaw); }
void Player::AddCameraPitch(float pitch) { Camera::AddPitch(pitch); }
void Player::AddCameraYaw(float yaw) { Camera::AddYaw(yaw); }

Math::Vector3 Player::GetCameraFrontVector() { return Camera::GetFrontVector(); }
Math::Vector3 Player::GetCameraUpVector() { return Camera::GetUpVector(); }

DirectX::XMMATRIX Player::CameraView() { return Camera::View(); }

void Player::UpdatePhysics(float deltaTime) {
	m_rigidBody.StepSimulation(m_position, deltaTime);
}