#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class EarthGolem : public PlatformerEnemy
{
public:
	static EarthGolem* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyEarthGolem;

private:
	EarthGolem(ValueMap* initProperties);
	~EarthGolem();
};
