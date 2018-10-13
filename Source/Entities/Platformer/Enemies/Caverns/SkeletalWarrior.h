#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletalWarrior : public PlatformerEnemy
{
public:
	static SkeletalWarrior * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemySkeletalWarrior;

private:
	SkeletalWarrior(ValueMap* initProperties);
	~SkeletalWarrior();
};
