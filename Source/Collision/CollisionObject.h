#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Collision/Collision.h"

using namespace cocos2d;

class CollisionObject
{
public:
	CollisionObject();
	~CollisionObject();

	PhysicsBody * physicsBody;
	Collision::CollisionGroup collisionGroup;
};

