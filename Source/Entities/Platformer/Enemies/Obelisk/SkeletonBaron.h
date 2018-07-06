#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonBaron : public PlatformerEnemy
{
public:
	static SkeletonBaron * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletonBaron;

private:
	SkeletonBaron(ValueMap* initProperties);
	~SkeletonBaron();
};
