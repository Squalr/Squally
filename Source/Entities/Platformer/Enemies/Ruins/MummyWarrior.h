#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class MummyWarrior : public PlatformerEnemy
{
public:
	static MummyWarrior * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyMummyWarrior;

private:
	MummyWarrior(ValueMap* initProperties);
	~MummyWarrior();
};
