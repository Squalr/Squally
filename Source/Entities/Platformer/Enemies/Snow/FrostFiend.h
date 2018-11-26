#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class FrostFiend : public PlatformerEnemy
{
public:
	static FrostFiend* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyFrostFiend;

private:
	FrostFiend(ValueMap* initProperties);
	~FrostFiend();
};
