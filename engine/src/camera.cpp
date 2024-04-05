#include "camera.h"

Camera::Camera(XMVECTOR startPosition) : m_position(startPosition), m_up(XMVectorSet(0, 1, 0, 0)), m_forward(XMVectorSet(0, 0, -1, 0)) {}

Camera::~Camera() {}

void Camera::MoveToPosition(XMVECTOR position) { m_position = position; }
void Camera::MoveByVector(XMVECTOR vector) { m_position += vector; }

XMMATRIX Camera::View() { return XMMatrixLookAtLH(m_position, m_forward, m_up); }