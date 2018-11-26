#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class DemonGrunt : public PlatformerEnemy
{
public:
	static DemonGrunt* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyDemonGrunt;

private:
	DemonGrunt(ValueMap* initProperties);
	~DemonGrunt();
};
