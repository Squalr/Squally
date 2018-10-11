#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletalBaron : public PlatformerEnemy
{
public:
	static SkeletalBaron * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletalBaron;

private:
	SkeletalBaron(ValueMap* initProperties);
	~SkeletalBaron();
};
