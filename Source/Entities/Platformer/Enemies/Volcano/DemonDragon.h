#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonDragon : public PlatformerEnemy
{
public:
	static DemonDragon * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyDemonDragon;

private:
	DemonDragon(ValueMap* initProperties);
	~DemonDragon();
};
