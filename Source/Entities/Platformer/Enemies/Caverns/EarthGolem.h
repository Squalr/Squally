#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class EarthGolem : public PlatformerEnemy
{
public:
	static EarthGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyEarthGolem;

private:
	EarthGolem(ValueMap* initProperties);
	~EarthGolem();
};
