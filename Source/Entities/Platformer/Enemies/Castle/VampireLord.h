#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class VampireLord : public PlatformerEnemy
{
public:
	static VampireLord* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyVampireLord;

private:
	VampireLord(ValueMap* initProperties);
	~VampireLord();
};
