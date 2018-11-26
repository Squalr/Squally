#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class ToySoldierGoblin : public PlatformerEnemy
{
public:
	static ToySoldierGoblin* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyToySoldierGoblin;

private:
	ToySoldierGoblin(ValueMap* initProperties);
	~ToySoldierGoblin();
};
