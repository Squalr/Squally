#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class DemonWarrior : public PlatformerEnemy
{
public:
	static DemonWarrior* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyDemonWarrior;

private:
	DemonWarrior(ValueMap* initProperties);
	~DemonWarrior();
};
