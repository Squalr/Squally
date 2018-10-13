#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class OrcBomber : public PlatformerEnemy
{
public:
	static OrcBomber * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyOrcBomber;

private:
	OrcBomber(ValueMap* initProperties);
	~OrcBomber();
};
