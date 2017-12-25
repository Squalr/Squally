#pragma once
#include "cocos2d.h"
#include "CollisionObject.h"
#include "Resources.h"
#include "Collision/TileCollision.h"

using namespace cocos2d;

class CollisionObject : public Node
{
public:
	static CollisionObject* create(Size size);
	static CollisionObject* create(Vec2* points, int count);

	const static enum CollisionGroup
	{
		Solid = 1 << 1,
		PassThrough = 1 << 2,
		Water = 1 << 3,
		Lava = 1 << 4,

		Liquid = Water | Lava,
		Entity = Solid | PassThrough | Water | Lava,
		All = Solid | PassThrough | Water | Lava
	};

	void SetCollisionGroup(CollisionGroup newCollisionGroup);

private:
	CollisionObject(PhysicsBody* initPhysicsBody);
	~CollisionObject();

	void InitializeListeners();
	bool OnContactBegin(PhysicsContact &contact);

	PhysicsBody * physicsBody;
	CollisionGroup collisionGroup;
};

