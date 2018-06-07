#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class CollisionKeys
{
public:
	static const std::string CollisionTypeProperty;
	static const std::string CollisionTypeSolid;
	static const std::string CollisionTypeWater;
	static const std::string CollisionTypeSolidNpc;
	static const std::string CollisionTypeSolidNpcFlying;

	static const std::string CollisionPointsProperty;
};
