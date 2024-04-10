#include "camera.h"

Camera::Camera(XMVECTOR startPosition) : m_position(startPosition), m_up(XMVectorSet(0, 1, 0, 0)), m_forward(XMVectorSet(0, 0, -1, 0)), m_yaw(0.0f), m_pitch(0.0f) {}

Camera::~Camera() {}

void Camera::MoveToPosition(XMVECTOR position) { m_position = position; }
void Camera::MoveByVector(XMVECTOR vector) { m_position += vector; }

void Camera::SetPitch(float pitch) {
	m_pitch = pitch;

	if (m_pitch > 89.0f) { m_pitch = 89.0f; }
	if (m_pitch < -89.0f) { m_pitch = -89.0f; }

	XMFLOAT4 dir;
	XMStoreFloat4(&dir, m_forward);
	dir.y = sin(XMConvertToRadians(m_pitch));

	m_forward = XMLoadFloat4(&dir);
	m_forward = XMVector4Normalize(m_forward);
}

void Camera::SetYaw(float yaw) {
	m_yaw = yaw;

	XMFLOAT4 dir;
	XMStoreFloat4(&dir, m_forward);
	dir.x = cos(XMConvertToRadians(m_yaw)) * cos(XMConvertToRadians(m_pitch));
	dir.z = sin(XMConvertToRadians(m_yaw)) * cos(XMConvertToRadians(m_pitch));

	m_forward = XMLoadFloat4(&dir);
	m_forward = XMVector4Normalize(m_forward);
}

void Camera::AddPitch(float pitch) { 
	m_pitch += pitch;

	XMFLOAT4 dir;
	XMStoreFloat4(&dir, m_forward);
	dir.y = sin(XMConvertToRadians(m_pitch));

	m_forward = XMLoadFloat4(&dir);
	m_forward = XMVector4Normalize(m_forward);

	if (m_pitch > 89.0f) { m_pitch = 89.0f; }
	if (m_pitch < -89.0f) { m_pitch = -89.0f; }
}

void Camera::AddYaw(float yaw) { 
	m_yaw += yaw;

	XMFLOAT4 dir;
	XMStoreFloat4(&dir, m_forward);
	dir.x = cos(XMConvertToRadians(m_yaw)) * cos(XMConvertToRadians(m_pitch));
	dir.z = sin(XMConvertToRadians(m_yaw)) * cos(XMConvertToRadians(m_pitch));

	m_forward = XMLoadFloat4(&dir);
	m_forward = XMVector4Normalize(m_forward);
}

XMVECTOR Camera::GetFrontVector() { return m_forward; }
XMVECTOR Camera::GetUpVector() { return m_up; }

XMMATRIX Camera::View() { return XMMatrixLookAtLH(m_position, m_position + m_forward, m_up); }