#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossKrampus : public PlatformerEnemy
{
public:
	static BossKrampus * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossKrampus;

private:
	BossKrampus(ValueMap* initProperties);
	~BossKrampus();
};
