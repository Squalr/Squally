#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonPriestess : public PlatformerEnemy
{
public:
	static SkeletonPriestess * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemySkeletonPriestess;

private:
	SkeletonPriestess(ValueMap* initProperties);
	~SkeletonPriestess();
};
