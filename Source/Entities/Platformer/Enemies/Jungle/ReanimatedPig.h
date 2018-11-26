#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class ReanimatedPig : public PlatformerEnemy
{
public:
	static ReanimatedPig* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyReanimatedPig;

private:
	ReanimatedPig(ValueMap* initProperties);
	~ReanimatedPig();
};
