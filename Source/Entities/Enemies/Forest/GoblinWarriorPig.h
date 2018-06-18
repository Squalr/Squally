#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinWarriorPig : public Enemy
{
public:
	static GoblinWarriorPig * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGoblinWarriorPig;

private:
	GoblinWarriorPig(ValueMap* initProperties);
	~GoblinWarriorPig();
};
