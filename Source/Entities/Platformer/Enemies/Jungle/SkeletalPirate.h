#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletalPirate : public PlatformerEnemy
{
public:
	static SkeletalPirate * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemySkeletalPirate;

private:
	SkeletalPirate(ValueMap* initProperties);
	~SkeletalPirate();
};
