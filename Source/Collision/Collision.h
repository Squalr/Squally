#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"

using namespace cocos2d;

class Collision
{
public:
	static Layer* initializeCollision(ValueVector collisionObjects);
	static PhysicsShape* getCollidingObject(PhysicsBody* self, PhysicsContact &contact);
	static bool isContactBelow(Node* node, PhysicsContact &contact);

	const static enum CollisionGroup
	{
		Solid = 1 << 1,
		PassThrough = 1 << 2,
		Player = 1 << 3,
		Enemy = 1 << 4,
		SolidNpc = 1 << 5,
		FlyingNpc = 1 << 6,
		Water = 1 << 7,
		Lava = 1 << 8,

		SET_Solids = Solid | PassThrough,
		SET_Liquids = Water | Lava,
		SET_Player = SET_Solids | SET_Liquids | Enemy,
		SET_Npc = SET_Solids | SET_Liquids | Player | SolidNpc | FlyingNpc,
	};
};
