#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class RockGolem : public PlatformerEnemy
{
public:
	static RockGolem * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyRockGolem;

private:
	RockGolem(ValueMap* initProperties);
	~RockGolem();
};
