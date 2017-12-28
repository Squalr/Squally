#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Utils/Utils.h"
#include "Collision/CollisionObject.h"
#include "Collision/CategoryGroup.h"

using namespace cocos2d;

class Collision
{
public:
	static Layer* initializeCollision(ValueVector collisionObjects);
};
