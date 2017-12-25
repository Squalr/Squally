#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Collision
{
public:
	static PhysicsShape* GetCollidingObject(PhysicsBody* self, PhysicsContact &contact);
	static bool IsContactBelow(Node* node, PhysicsContact &contact);

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
};

