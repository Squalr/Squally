#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossWitch : public PlatformerEnemy
{
public:
	static BossWitch * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossWitch;

private:
	BossWitch(ValueMap* initProperties);
	~BossWitch();
};
