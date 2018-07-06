#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonCleaver : public PlatformerEnemy
{
public:
	static SkeletonCleaver * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletonCleaver;

private:
	SkeletonCleaver(ValueMap* initProperties);
	~SkeletonCleaver();
};
