#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class PenguinWarrior : public PlatformerEnemy
{
public:
	static PenguinWarrior * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyPenguinWarrior;

private:
	PenguinWarrior(ValueMap* initProperties);
	~PenguinWarrior();
};
