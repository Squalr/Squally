#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class CollisionGroups
{
public:
	CollisionGroups();
	~CollisionGroups();

	const static enum CollisionGroupsEnum
	{
		Solid,
		PassThrough,
		Water,
		Lava,
		Entity = Solid | PassThrough | Water | Lava
	};
};

