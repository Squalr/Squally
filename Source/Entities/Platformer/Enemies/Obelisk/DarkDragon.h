#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class DarkDragon : public PlatformerEnemy
{
public:
	static DarkDragon * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyDarkDragon;

private:
	DarkDragon(ValueMap* initProperties);
	~DarkDragon();
};
