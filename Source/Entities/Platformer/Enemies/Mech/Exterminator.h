#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Exterminator : public PlatformerEnemy
{
public:
	static Exterminator* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyExterminator;

private:
	Exterminator(ValueMap* initProperties);
	~Exterminator();
};
