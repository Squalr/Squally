#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonArcher : public PlatformerEnemy
{
public:
	static SkeletonArcher * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletonArcher;

private:
	SkeletonArcher(ValueMap* initProperties);
	~SkeletonArcher();
};
