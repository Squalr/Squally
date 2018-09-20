#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossJack : public PlatformerEnemy
{
public:
	static BossJack * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossJack;

private:
	BossJack(ValueMap* initProperties);
	~BossJack();
};
