#include "physics_object.h"

Physics::Object::Object(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Math::Vector3 position, float mass, Math::Vector3 colliderMin, Math::Vector3 colliderMax, UINT singleVertexSize, UINT vertexCount, void* vertices, UINT indexCount, DWORD* indices, LPCWSTR texturePath) :
	RigidBody(position, mass, Math::Vector3(0.0f, -50.0f, 0.0f), 1.0f),
	Model(device, deviceContext, singleVertexSize, vertexCount, vertices, indexCount, indices, texturePath),
	m_collider(colliderMin, colliderMax),
	m_groundedCollider(colliderMin - Math::Vector3(0.0f, -0.1f, 0.0f), colliderMax - Math::Vector3(0.0f, -0.1f, 0.0f)) {}

Physics::Object::~Object() {}

void Physics::Object::Update(Time* time) {
	m_position = GetInterpolatedPosition(time);
}

void Physics::Object::TestCollision(Physics::AABBCollider& other, Math::Vector3 otherPosition) {
	Physics::Collision c;

	if (m_collider.TestCollision(c, m_position, other, otherPosition)) {
		// Correct collision by moving out of the collided object
		m_physicsPosition += c.normal * c.depth;
	}

	// Grounding collider is a additional collider placed under the object to determin
	// if it is colliding with the floor.
	if (m_groundedCollider.TestCollision(m_position, other, otherPosition)) {
		// Ground the object of it has no upwards velocity
		if (m_velocity.y < 0.0f) m_grounded = true;
	}
	else m_grounded = false;
}

Physics::AABBCollider* Physics::Object::Collider() { return &m_collider; }