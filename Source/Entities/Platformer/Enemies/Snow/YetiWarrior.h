#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class YetiWarrior : public PlatformerEnemy
{
public:
	static YetiWarrior* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyYetiWarrior;

private:
	YetiWarrior(ValueMap* initProperties);
	~YetiWarrior();
};
