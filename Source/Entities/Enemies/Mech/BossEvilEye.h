#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossEvilEye : public Enemy
{
public:
	static BossEvilEye * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossEvilEye;

private:
	BossEvilEye(ValueMap* initProperties);
	~BossEvilEye();
};
