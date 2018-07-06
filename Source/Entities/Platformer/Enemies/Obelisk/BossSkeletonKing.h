#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossSkeletonKing : public PlatformerEnemy
{
public:
	static BossSkeletonKing * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossSkeletonKing;

private:
	BossSkeletonKing(ValueMap* initProperties);
	~BossSkeletonKing();
};
