#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class SkeletalPriestess : public PlatformerEnemy
{
public:
	static SkeletalPriestess* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemySkeletalPriestess;

private:
	SkeletalPriestess(ValueMap* initProperties);
	~SkeletalPriestess();
};
