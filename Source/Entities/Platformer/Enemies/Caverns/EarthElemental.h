#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class EarthElemental : public PlatformerEnemy
{
public:
	static EarthElemental * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyEarthElemental;

private:
	EarthElemental(ValueMap* initProperties);
	~EarthElemental();
};
