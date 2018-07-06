#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class PigDemon : public PlatformerEnemy
{
public:
	static PigDemon * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyPigDemon;

private:
	PigDemon(ValueMap* initProperties);
	~PigDemon();
};
