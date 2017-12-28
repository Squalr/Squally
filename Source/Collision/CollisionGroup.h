#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

const static enum CollisionGroup
{
	G_None = 0,
	G_Solid = 1 << 1,
	G_PassThrough = 1 << 2,
	G_Player = 1 << 3,
	G_Enemy = 1 << 4,
	G_SolidNpc = 1 << 5,
	G_FlyingNpc = 1 << 6,
	G_Water = 1 << 7,
	G_Lava = 1 << 8,

	SET_Solids = G_Solid | G_PassThrough,
	SET_Liquids = G_Water | G_Lava,
	SET_Player = SET_Solids | SET_Liquids | G_Enemy,
	SET_Npc = SET_Solids | SET_Liquids | G_Player | G_SolidNpc | G_FlyingNpc,
	SET_Entities = G_Player | G_Enemy,
	SET_All = G_Solid | G_PassThrough | G_Player | G_Enemy | G_SolidNpc | G_FlyingNpc | G_Water | G_Lava,
};
