#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class FrostShooter : public PlatformerEnemy
{
public:
	static FrostShooter * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyFrostShooter;

private:
	FrostShooter(ValueMap* initProperties);
	~FrostShooter();
};
