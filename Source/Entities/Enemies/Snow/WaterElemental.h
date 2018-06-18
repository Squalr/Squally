#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class WaterElemental : public Enemy
{
public:
	static WaterElemental * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyWaterElemental;

private:
	WaterElemental(ValueMap* initProperties);
	~WaterElemental();
};
