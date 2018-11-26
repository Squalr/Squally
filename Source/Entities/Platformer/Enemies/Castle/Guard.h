#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Guard : public PlatformerEnemy
{
public:
	static Guard* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyGuard;

private:
	Guard(ValueMap* initProperties);
	~Guard();
};
