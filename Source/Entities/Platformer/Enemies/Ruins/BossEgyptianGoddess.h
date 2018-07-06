#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossEgyptianGoddess : public PlatformerEnemy
{
public:
	static BossEgyptianGoddess * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossEgyptianGoddess;

private:
	BossEgyptianGoddess(ValueMap* initProperties);
	~BossEgyptianGoddess();
};
