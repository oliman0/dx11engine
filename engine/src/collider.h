// collider.h
// This handles collision detection through AABBs

#pragma once

#include "engine_math.h"

namespace Physics {

	struct Collision {
		Collision();
		~Collision();

		Math::Vector3 normal;
		float depth;

		bool collision;
	};

	struct AABBCollider
	{
		AABBCollider(Math::Vector3 min, Math::Vector3 max);
		~AABBCollider();

		bool TestCollision(Collision& inout_collisionData, Math::Vector3 position, AABBCollider& other, Math::Vector3 otherPosition);
		bool TestCollision(Math::Vector3 position, AABBCollider& other, Math::Vector3 otherPosition);

		Math::Vector3 min;
		Math::Vector3 max;
	};
	
	namespace CollisionTest {
		bool AABBTestCollision(Collision& inout_collisionData, AABBCollider& a, Math::Vector3 aPosition, AABBCollider& b, Math::Vector3 bPosition);
		bool AABBTestCollision(AABBCollider& a, Math::Vector3 aPosition, AABBCollider& b, Math::Vector3 bPosition);
	}
}