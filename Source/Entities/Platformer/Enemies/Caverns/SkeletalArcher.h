#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class SkeletalArcher : public PlatformerEnemy
{
public:
	static SkeletalArcher * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemySkeletalArcher;

private:
	SkeletalArcher(ValueMap* initProperties);
	~SkeletalArcher();
};
