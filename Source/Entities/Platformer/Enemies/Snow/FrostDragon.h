#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class FrostDragon : public PlatformerEnemy
{
public:
	static FrostDragon * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyFrostDragon;

private:
	FrostDragon(ValueMap* initProperties);
	~FrostDragon();
};
