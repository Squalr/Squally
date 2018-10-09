#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class ZombieSpearman : public PlatformerEnemy
{
public:
	static ZombieSpearman * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyZombieSpearman;

private:
	ZombieSpearman(ValueMap* initProperties);
	~ZombieSpearman();
};
