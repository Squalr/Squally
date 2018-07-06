#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonNecromancer : public PlatformerEnemy
{
public:
	static SkeletonNecromancer * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletonNecromancer;

private:
	SkeletonNecromancer(ValueMap* initProperties);
	~SkeletonNecromancer();
};
