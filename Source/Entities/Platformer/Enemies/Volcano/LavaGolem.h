#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class LavaGolem : public PlatformerEnemy
{
public:
	static LavaGolem* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyLavaGolem;

private:
	LavaGolem(ValueMap* initProperties);
	~LavaGolem();
};
