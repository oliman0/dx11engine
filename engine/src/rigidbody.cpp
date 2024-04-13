#include "rigidbody.h"

Physics::RigidBody::RigidBody(float mass, Math::Vector3 gravity) : m_mass(mass), m_velocity(0.0f), m_force(0.0f), m_gravity(gravity), m_grounded(false) {}
Physics::RigidBody::~RigidBody() {}

void Physics::RigidBody::StepSimulation(Math::Vector3& position, float deltaTime) {
	if (!m_grounded) m_force += m_gravity * m_mass;
	if (m_grounded && m_velocity.y < 0.0f) m_velocity.y = 0.0f;

	m_velocity += m_force / m_mass * deltaTime;
	position += m_velocity * deltaTime;

	m_force = 0.0f;
}

void Physics::RigidBody::AddForce(Math::Vector3 force) { m_force += force; }
void Physics::RigidBody::SetForce(Math::Vector3 force) { m_force = force; }
void Physics::RigidBody::SetVelocity(Math::Vector3 velocity) { m_velocity = velocity; }

Math::Vector3 Physics::RigidBody::GetForce() { return m_force; }
Math::Vector3 Physics::RigidBody::GetVelocity() { return m_velocity; }
Math::Vector3 Physics::RigidBody::GetGravity() { return m_gravity; }
float Physics::RigidBody::GetMass() { return m_mass; }

void Physics::RigidBody::SetGravity(Math::Vector3 gravity) { m_gravity = gravity; }
void Physics::RigidBody::SetMass(float mass) { m_mass = mass; }

void Physics::RigidBody::SetGrounded(bool grounded) { m_grounded = grounded; }
bool Physics::RigidBody::GetGrounded() { return m_grounded; }