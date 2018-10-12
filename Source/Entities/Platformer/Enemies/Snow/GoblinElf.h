#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinElf : public PlatformerEnemy
{
public:
	static GoblinElf * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyGoblinElf;

private:
	GoblinElf(ValueMap* initProperties);
	~GoblinElf();
};
