#pragma once

#include "engine_math.h"

namespace Physics {

	class RigidBody
	{
	public:
		RigidBody(float mass, Math::Vector3 gravity);
		~RigidBody();

		void StepSimulation(Math::Vector3& position, float deltaTime);

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

	private:
		Math::Vector3 m_velocity;
		Math::Vector3 m_force;
		float m_mass;

		bool m_grounded;
		
		Math::Vector3 m_gravity;
	};

}