#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class JungleDragon : public PlatformerEnemy
{
public:
	static JungleDragon * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyJungleDragon;

private:
	JungleDragon(ValueMap* initProperties);
	~JungleDragon();
};
