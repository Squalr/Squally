#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class YetiWarrior : public Enemy
{
public:
	static YetiWarrior * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyYetiWarrior;

private:
	YetiWarrior(ValueMap* initProperties);
	~YetiWarrior();
};
