#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

const static enum CategoryGroup
{
	G_None = 0,
	G_Solid = 1 << 1,
	G_PassThrough = 1 << 2,
	G_Player = 1 << 3,
	G_Enemy = 1 << 4,
	G_EnemyFlying = 1 << 5,
	G_Force = 1 << 6,
	G_SolidNpc = 1 << 7,
	G_SolidFlyingNpc = 1 << 8,
	G_Water = 1 << 9,
	G_Lava = 1 << 10,
};
