#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Ghost : public PlatformerEnemy
{
public:
	static Ghost * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGhost;

private:
	Ghost(ValueMap* initProperties);
	~Ghost();
};
