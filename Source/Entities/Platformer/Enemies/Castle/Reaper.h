#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Reaper : public PlatformerEnemy
{
public:
	static Reaper * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyReaper;

private:
	Reaper(ValueMap* initProperties);
	~Reaper();
};
