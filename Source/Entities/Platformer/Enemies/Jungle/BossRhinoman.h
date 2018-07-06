#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossRhinoman : public PlatformerEnemy
{
public:
	static BossRhinoman * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossRhinoman;

private:
	BossRhinoman(ValueMap* initProperties);
	~BossRhinoman();
};
