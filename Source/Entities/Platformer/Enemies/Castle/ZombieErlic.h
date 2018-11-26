#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class ZombieErlic : public PlatformerEnemy
{
public:
	static ZombieErlic* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyZombieErlic;

private:
	ZombieErlic(ValueMap* initProperties);
	~ZombieErlic();
};
