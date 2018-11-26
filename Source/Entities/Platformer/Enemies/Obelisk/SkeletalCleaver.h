#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class SkeletalCleaver : public PlatformerEnemy
{
public:
	static SkeletalCleaver* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemySkeletalCleaver;

private:
	SkeletalCleaver(ValueMap* initProperties);
	~SkeletalCleaver();
};
