#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class BlackWidow : public PlatformerEnemy
{
public:
	static BlackWidow* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyBlackWidow;

private:
	BlackWidow(ValueMap* initProperties);
	~BlackWidow();
};
