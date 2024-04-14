#include "camera.h"

Camera::Camera(Math::Vector3 startPosition) : m_position(startPosition), m_up(0, 1, 0), m_forward(0, 0, -1), m_yaw(0.0f), m_pitch(0.0f) {}

Camera::~Camera() {}

Math::Vector3 Camera::GetPosition() { return m_position; }
void Camera::SetPosition(Math::Vector3 position) { m_position = position; }
void Camera::MoveByVector(Math::Vector3 vector) { m_position += vector; }

void Camera::SetPitch(float pitch) {
	m_pitch = pitch;

	m_forward.y = sinf(Math::Radians(m_pitch));

	m_forward = Math::Normalize(m_forward);

	if (m_pitch > 89.0f) { m_pitch = 89.0f; }
	if (m_pitch < -89.0f) { m_pitch = -89.0f; }
}

void Camera::SetYaw(float yaw) {
	m_yaw = yaw;

	m_forward.x = cosf(Math::Radians(m_yaw)) * cosf(Math::Radians(m_pitch));
	m_forward.z = sinf(Math::Radians(m_yaw)) * cosf(Math::Radians(m_pitch));

	m_forward = Math::Normalize(m_forward);
}

void Camera::AddPitch(float pitch) { 
	m_pitch += pitch;

	m_forward.y = sinf(Math::Radians(m_pitch));

	m_forward = Math::Normalize(m_forward);

	if (m_pitch > 89.0f) { m_pitch = 89.0f; }
	if (m_pitch < -89.0f) { m_pitch = -89.0f; }
}

void Camera::AddYaw(float yaw) { 
	m_yaw += yaw;

	m_forward.x = cosf(Math::Radians(m_yaw)) * cosf(Math::Radians(m_pitch));
	m_forward.z = sinf(Math::Radians(m_yaw)) * cosf(Math::Radians(m_pitch));

	m_forward = Math::Normalize(m_forward);
}

Math::Vector3 Camera::GetFrontVector() { return m_forward; }
Math::Vector3 Camera::GetUpVector() { return m_up; }

DirectX::XMMATRIX Camera::View() { return DirectX::XMMatrixLookAtLH(m_position.GetXMVector(), (m_position + m_forward).GetXMVector(), m_up.GetXMVector()); }