#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class OrcWarrior : public Enemy
{
public:
	static OrcWarrior * create();

	static const std::string KeyEnemyOrcWarrior;

private:
	OrcWarrior();
	~OrcWarrior();
};
