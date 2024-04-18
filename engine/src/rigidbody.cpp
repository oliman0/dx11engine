#include "rigidbody.h"

Physics::RigidBody::RigidBody(Math::Vector3 position, float mass, Math::Vector3 gravity, float friction) : m_mass(mass), m_velocity(0.0f), m_force(0.0f), m_gravity(gravity), m_grounded(false), m_physicsPosition(position), m_oldPosition(0.0f), m_friction(friction) {}
Physics::RigidBody::~RigidBody() {}

void Physics::RigidBody::UpdatePhysics(float deltaTime) {
	m_oldPosition = m_physicsPosition;

	// Apply Gravity
	if (!m_grounded) m_force += m_gravity * m_mass;

	// If on ground then keep y velocity above 0
	if (m_grounded && m_velocity.y < 0.0f) m_velocity.y = 0.0f;

	// Apply ground friction
	m_velocity.x *= m_friction;
	m_velocity.z *= m_friction;
	if (std::abs(m_velocity.x) < 0.1f) m_velocity.x = 0.0f;
	if (std::abs(m_velocity.z) < 0.1f) m_velocity.z = 0.0f;

	// Euler Method
	m_velocity += m_force / m_mass * deltaTime;
	m_physicsPosition += m_velocity * deltaTime;

	m_force = 0.0f;
}

Math::Vector3 Physics::RigidBody::GetInterpolatedPosition(Time* time) {
	// Time elapsed since last tick
	float tickElapsed = time->GetTimerTime(time->GetTickTimer());
	
	// Elapsed time / Time inbetween ticks
	float tickPercentage = tickElapsed / (1.0f / time->GetTickRate());

	// If the percentage is very small then the tick has just started, BUT the fixedupdate is called
	// after the perframe update so the new position hasn't been calculated yet which causes the object
	// to snap back to its old position. So instead we return the position it should be at by the end of the tick.
	if (tickPercentage < 0.01f) return m_physicsPosition;

	// Position inbetween expected and old position scaled by the percentage
	// of the time between the last tick and the next
	// (thats a terrible explaination but its just some interpolation)
	return m_oldPosition + (m_physicsPosition - m_oldPosition) * tickPercentage;
}

Math::Vector3 Physics::RigidBody::GetPosition() { return m_physicsPosition; }
void Physics::RigidBody::SetPosition(Math::Vector3 position) { m_physicsPosition = position; }
void Physics::RigidBody::MoveByVector(Math::Vector3 vector) { m_physicsPosition += vector; }

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