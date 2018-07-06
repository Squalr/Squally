#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class TikiWarrior : public PlatformerEnemy
{
public:
	static TikiWarrior * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyTikiWarrior;

private:
	TikiWarrior(ValueMap* initProperties);
	~TikiWarrior();
};
