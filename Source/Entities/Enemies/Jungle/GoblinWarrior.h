#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinWarrior : public Enemy
{
public:
	static GoblinWarrior * create();

	static const std::string KeyEnemyGoblinWarrior;

private:
	GoblinWarrior();
	~GoblinWarrior();
};
