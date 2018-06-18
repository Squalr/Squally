#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class AnubisWarrior : public Enemy
{
public:
	static AnubisWarrior * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyAnubisWarrior;

private:
	AnubisWarrior(ValueMap* initProperties);
	~AnubisWarrior();
};
