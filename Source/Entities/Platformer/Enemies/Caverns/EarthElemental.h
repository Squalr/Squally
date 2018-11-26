#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class EarthElemental : public PlatformerEnemy
{
public:
	static EarthElemental* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyEarthElemental;

private:
	EarthElemental(ValueMap* initProperties);
	~EarthElemental();
};
