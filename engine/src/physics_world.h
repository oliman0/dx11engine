#pragma once

#include <vector>

#include "physics_object.h"

class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void UpdatePhysics();

	void AddObject(Physics::Object* obj);
	std::vector<Physics::Object*> Objects();

	std::vector<Physics::Collision> TestCollision(Physics::AABBCollider& collider, Math::Vector3 position);
	bool TestCollisionSingle(Physics::AABBCollider& collider, Math::Vector3 position);

private:
	std::vector<Physics::Object*> m_pObjects;
};

