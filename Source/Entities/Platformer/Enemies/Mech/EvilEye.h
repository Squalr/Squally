#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossEvilEye : public PlatformerEnemy
{
public:
	static BossEvilEye * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyBossEvilEye;

private:
	BossEvilEye(ValueMap* initProperties);
	~BossEvilEye();
};
