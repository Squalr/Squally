#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonShaman : public PlatformerEnemy
{
public:
	static DemonShaman * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyDemonShaman;

private:
	DemonShaman(ValueMap* initProperties);
	~DemonShaman();
};
