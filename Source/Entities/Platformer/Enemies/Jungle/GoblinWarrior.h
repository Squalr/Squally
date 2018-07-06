#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinWarrior : public PlatformerEnemy
{
public:
	static GoblinWarrior * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGoblinWarrior;

private:
	GoblinWarrior(ValueMap* initProperties);
	~GoblinWarrior();
};
