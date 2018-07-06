#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonMage : public PlatformerEnemy
{
public:
	static SkeletonMage * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletonMage;

private:
	SkeletonMage(ValueMap* initProperties);
	~SkeletonMage();
};
