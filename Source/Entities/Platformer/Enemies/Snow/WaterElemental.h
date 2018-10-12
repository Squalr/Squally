#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class WaterElemental : public PlatformerEnemy
{
public:
	static WaterElemental * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyWaterElemental;

private:
	WaterElemental(ValueMap* initProperties);
	~WaterElemental();
};
