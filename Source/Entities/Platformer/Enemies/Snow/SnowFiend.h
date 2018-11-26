#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class SnowFiend : public PlatformerEnemy
{
public:
	static SnowFiend* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemySnowFiend;

private:
	SnowFiend(ValueMap* initProperties);
	~SnowFiend();
};
