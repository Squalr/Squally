#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossWitch : public Enemy
{
public:
	static BossWitch * create();

	static const std::string KeyEnemyBossWitch;

private:
	BossWitch();
	~BossWitch();
};
