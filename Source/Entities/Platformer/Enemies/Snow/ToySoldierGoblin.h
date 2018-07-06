#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class ToySoldierGoblin : public PlatformerEnemy
{
public:
	static ToySoldierGoblin * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyToySoldierGoblin;

private:
	ToySoldierGoblin(ValueMap* initProperties);
	~ToySoldierGoblin();
};
