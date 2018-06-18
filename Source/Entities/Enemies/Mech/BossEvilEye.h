#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossEvilEye : public Enemy
{
public:
	static BossEvilEye * create();

	static const std::string KeyEnemyBossEvilEye;

private:
	BossEvilEye();
	~BossEvilEye();
};
