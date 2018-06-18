#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossSkeletonKing : public Enemy
{
public:
	static BossSkeletonKing * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossSkeletonKing;

private:
	BossSkeletonKing(ValueMap* initProperties);
	~BossSkeletonKing();
};
