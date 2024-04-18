#include "physics_world.h"

PhysicsWorld::PhysicsWorld() {}
PhysicsWorld::~PhysicsWorld() {
	
}

void PhysicsWorld::UpdatePhysics() {
	for (Physics::Object* obj : m_pObjects) {
		obj->Delete();
	}
}

void PhysicsWorld::AddObject(Physics::Object* obj) { m_pObjects.push_back(obj); }

std::vector<Physics::Object*> PhysicsWorld::Objects() { return m_pObjects; }

std::vector<Physics::Collision> PhysicsWorld::TestCollision(Physics::AABBCollider & collider, Math::Vector3 position) {
	std::vector<Physics::Collision> result;

	for (Physics::Object* obj : m_pObjects) {
		Physics::Collision c;

		if (Physics::CollisionTest::AABBTestCollision(c, collider, position, *obj->Collider(), obj->GetPosition())) {
			result.push_back(c);
		}
	}

	return result;
}

bool PhysicsWorld::TestCollisionSingle(Physics::AABBCollider& collider, Math::Vector3 position) {
	for (Physics::Object* obj : m_pObjects) {
		if (Physics::CollisionTest::AABBTestCollision(collider, position, *obj->Collider(), obj->GetPosition())) {
			return true;
		}
	}

	return false;
}