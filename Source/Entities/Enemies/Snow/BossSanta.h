#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossSanta : public Enemy
{
public:
	static BossSanta * create();

	static const std::string KeyEnemyBossSanta;

private:
	BossSanta();
	~BossSanta();
};
