#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonWarrior : public Enemy
{
public:
	static DemonWarrior * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyDemonWarrior;

private:
	DemonWarrior(ValueMap* initProperties);
	~DemonWarrior();
};
