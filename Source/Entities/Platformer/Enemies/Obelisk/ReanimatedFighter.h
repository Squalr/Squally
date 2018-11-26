#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class ReanimatedFighter : public PlatformerEnemy
{
public:
	static ReanimatedFighter* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyReanimatedFighter;

private:
	ReanimatedFighter(ValueMap* initProperties);
	~ReanimatedFighter();
};
