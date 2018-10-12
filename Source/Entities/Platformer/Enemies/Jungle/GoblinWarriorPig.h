#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinWarriorPig : public PlatformerEnemy
{
public:
	static GoblinWarriorPig * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyGoblinWarriorPig;

private:
	GoblinWarriorPig(ValueMap* initProperties);
	~GoblinWarriorPig();
};
