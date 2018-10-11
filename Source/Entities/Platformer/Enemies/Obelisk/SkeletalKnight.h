#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletalKnight : public PlatformerEnemy
{
public:
	static SkeletalKnight * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletalKnight;

private:
	SkeletalKnight(ValueMap* initProperties);
	~SkeletalKnight();
};
