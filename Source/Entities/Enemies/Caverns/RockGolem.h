#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class RockGolem : public Enemy
{
public:
	static RockGolem * create();

	static const std::string KeyEnemyRockGolem;

private:
	RockGolem();
	~RockGolem();
};
