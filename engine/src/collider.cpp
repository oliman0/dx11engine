#include "collider.h"
#include <vector>

Physics::Collision::Collision() : normal(0.0f), collision(false), depth(0.0f) {}
Physics::Collision::~Collision() {}

Physics::AABBCollider::AABBCollider(Math::Vector3 min, Math::Vector3 max) : min(min), max(max) {}
Physics::AABBCollider::~AABBCollider() {}

bool Physics::AABBCollider::TestCollision(Physics::Collision& inout_collisionData, Math::Vector3 position, AABBCollider& other, Math::Vector3 otherPosition) { return CollisionTest::AABBTestCollision(inout_collisionData, *this, position, other, otherPosition); }
bool Physics::AABBCollider::TestCollision(Math::Vector3 position, AABBCollider& other, Math::Vector3 otherPosition) { return CollisionTest::AABBTestCollision(*this, position, other, otherPosition); }

bool Physics::CollisionTest::AABBTestCollision(Collision& inout_collisionData, AABBCollider& a, Math::Vector3 aPosition, AABBCollider& b, Math::Vector3 bPosition) {
	Math::Vector3 aMin = a.min + aPosition;
	Math::Vector3 aMax = a.max + aPosition;
	Math::Vector3 bMin = b.min + bPosition;
	Math::Vector3 bMax = b.max + bPosition;

	if (aMin.x < bMax.x && aMax.x > bMin.x &&
		aMin.y < bMax.y && aMax.y > bMin.y &&
		aMin.z < bMax.z && aMax.z > bMin.z)
	{
		// If smallest is:
		// 0: +X Face Collision
		// 1: -X Face Collision
		// 2: +Y Face Colliison
		// 3: -Y Face Collision
		// 4: +Z Face Collision
		// 5: -Z Face Collision
		std::vector<float> dists{ std::abs(aMax.x - bMin.x), std::abs(aMin.x - bMax.x),
								  std::abs(aMax.y - bMin.y), std::abs(aMin.y - bMax.y),
								  std::abs(aMax.z - bMin.z), std::abs(aMin.z - bMax.z) };

		int i = (int)std::distance(std::begin(dists), std::min_element(std::begin(dists), std::end(dists)));

			  if (i == 0) { inout_collisionData.normal = Math::Vector3(-1, 0, 0); inout_collisionData.depth = dists[0]; }
		 else if (i == 1) { inout_collisionData.normal = Math::Vector3(1, 0, 0); inout_collisionData.depth = dists[1]; }
		 else if (i == 2) { inout_collisionData.normal = Math::Vector3(0, -1, 0); inout_collisionData.depth = dists[2]; }
		 else if (i == 3) { inout_collisionData.normal = Math::Vector3(0, 1, 0); inout_collisionData.depth = dists[3]; }
		 else if (i == 4) { inout_collisionData.normal = Math::Vector3(0, 0, -1); inout_collisionData.depth = dists[4]; }
		 else if (i == 5) { inout_collisionData.normal = Math::Vector3(0, 0, 1); inout_collisionData.depth = dists[5]; }

		inout_collisionData.collision = true;

		return true;
	}
	else {
		return false;
	}
}

bool Physics::CollisionTest::AABBTestCollision(AABBCollider& a, Math::Vector3 aPosition, AABBCollider& b, Math::Vector3 bPosition) {
	Math::Vector3 aMin = a.min + aPosition;
	Math::Vector3 aMax = a.max + aPosition;
	Math::Vector3 bMin = b.min + bPosition;
	Math::Vector3 bMax = b.max + bPosition;

	if ((aMin.x < bMax.x && aMax.x > bMin.x) &&
		(aMin.y < bMax.y && aMax.y > bMin.y) &&
		(aMin.z < bMax.z && aMax.z > bMin.z))
	{
		return true;
	}
	else {
		return false;
	}
}
