#pragma once
#include "cocos2d.h"
#include "Utils/Utils.h"
#include "Collision/Collision.h"

using namespace cocos2d;

static class TileCollision
{
public:

	static Layer* InitializeCollision(ValueVector collisionObjects);
};
