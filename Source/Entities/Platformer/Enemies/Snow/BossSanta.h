#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossSanta : public PlatformerEnemy
{
public:
	static BossSanta * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyBossSanta;

private:
	BossSanta(ValueMap* initProperties);
	~BossSanta();
};
