#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonWarrior : public PlatformerEnemy
{
public:
	static DemonWarrior * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyDemonWarrior;

private:
	DemonWarrior(ValueMap* initProperties);
	~DemonWarrior();
};
