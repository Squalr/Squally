#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletalArcher : public PlatformerEnemy
{
public:
	static SkeletalArcher * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletalArcher;

private:
	SkeletalArcher(ValueMap* initProperties);
	~SkeletalArcher();
};
