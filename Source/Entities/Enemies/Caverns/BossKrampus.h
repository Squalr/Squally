#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossKrampus : public Enemy
{
public:
	static BossKrampus * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossKrampus;

private:
	BossKrampus(ValueMap* initProperties);
	~BossKrampus();
};
