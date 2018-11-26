#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class OrcWarrior : public PlatformerEnemy
{
public:
	static OrcWarrior* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyOrcWarrior;

private:
	OrcWarrior(ValueMap* initProperties);
	~OrcWarrior();
};
