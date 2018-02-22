#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Entities/Npcs/NpcBase.h"
#include "Objects/Collision/CategoryGroup.h"

using namespace cocos2d;

class Skeleton : public NpcBase
{
public:
	static Skeleton * create();

private:
	Skeleton();
	~Skeleton();

	void update(float) override;

	Animation* idleAnimation;

	Sprite* skeletonSprite;
};
