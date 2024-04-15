// physics_object.h
// An object class that implements Colliders and RigidBody Physics

#pragma once

#include "rigidbody.h"
#include "collider.h"
#include "model.h"

namespace Physics {

	class Object : public RigidBody, public Model
	{
	public:
		Object(ID3D11Device* device, ID3D11DeviceContext* deviceContext, Math::Vector3 position, float mass, Math::Vector3 colliderMin, Math::Vector3 colliderMax, UINT singleVertexSize, UINT vertexCount, void* vertices, UINT indexCount, DWORD* indices, LPCWSTR texturePath);
		~Object();

		void Update(Time* time);

		void TestCollision(Physics::AABBCollider& other, Math::Vector3 otherPosition);

	private:
		Math::Vector3 m_position;

		AABBCollider m_collider;
		AABBCollider m_groundedCollider;
	};

}