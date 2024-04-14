#include "rigidbody.h"

Physics::RigidBody::RigidBody(Math::Vector3 position, float mass, Math::Vector3 gravity) : m_mass(mass), m_velocity(0.0f), m_force(0.0f), m_gravity(gravity), m_grounded(false), m_position(position), m_oldPosition(0.0f) {}
Physics::RigidBody::~RigidBody() {}

void Physics::RigidBody::StepSimulation(float deltaTime) {
	m_oldPosition = m_position;

	// Apply Gravity
	if (!m_grounded) m_force += m_gravity * m_mass;

	// If on ground then keep y velocity above 0
	if (m_grounded && m_velocity.y < 0.0f) m_velocity.y = 0.0f;

	// Euler Method
	m_velocity += m_force / m_mass * deltaTime;
	m_position += m_velocity * deltaTime;

	m_force = 0.0f;
}

Math::Vector3 Physics::RigidBody::GetInterpolatedPosition(Time* time) {
	// Time elapsed since last tick
	float tickElapsed = time->GetTimerTime(time->GetTickTimer());
	
	// Elapsed time / Time inbetween ticks
	float tickPercentage = tickElapsed / (1.0f / time->GetTickRate());

	// Position inbetween expected and old position scaled by the percentage
	// of the time between ticks
	// (thats a terrible explaination but its just some interpolation)
	return m_oldPosition + (m_position - m_oldPosition) * tickPercentage;
}

Math::Vector3 Physics::RigidBody::GetPosition() { return m_position; }
void Physics::RigidBody::SetPosition(Math::Vector3 position) { m_position = position; }
void Physics::RigidBody::MoveByVector(Math::Vector3 vector) { m_position += vector; }

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