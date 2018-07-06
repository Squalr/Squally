#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinSwordsman : public PlatformerEnemy
{
public:
	static GoblinSwordsman * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGoblinSwordsman;

private:
	GoblinSwordsman(ValueMap* initProperties);
	~GoblinSwordsman();
};
