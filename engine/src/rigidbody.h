// rigidbody.h
// Handles Rigidbody Physics and interpolation

#pragma once

#include "engine_math.h"
#include "timer.h"

namespace Physics {

	class RigidBody
	{
	public:
		RigidBody(Math::Vector3 position, float mass, Math::Vector3 gravity, float friction);
		~RigidBody();

		void UpdatePhysics(float deltaTime);

		Math::Vector3 GetPosition();
		void SetPosition(Math::Vector3 position);
		void MoveByVector(Math::Vector3 vector);

		void AddForce(Math::Vector3 force);
		void SetForce(Math::Vector3 force);
		void SetVelocity(Math::Vector3 velocity);

		Math::Vector3 GetForce();
		Math::Vector3 GetVelocity();
		Math::Vector3 GetGravity();
		float GetMass();

		void SetGravity(Math::Vector3 gravity);
		void SetMass(float mass);

		void SetGrounded(bool grounded);
		bool GetGrounded();

	protected:
		Math::Vector3 GetInterpolatedPosition(Time* time);

	protected:
		Math::Vector3 m_oldPosition;
		Math::Vector3 m_physicsPosition;

		Math::Vector3 m_velocity;
		Math::Vector3 m_force;
		float m_mass;
		float m_friction;

		bool m_grounded;
		
		Math::Vector3 m_gravity;
	};

}