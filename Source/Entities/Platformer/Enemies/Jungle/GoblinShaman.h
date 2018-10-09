#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class GoblinShaman : public PlatformerEnemy
{
public:
	static GoblinShaman * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGoblinShaman;

private:
	GoblinShaman(ValueMap* initProperties);
	~GoblinShaman();
};
