#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Exterminator : public PlatformerEnemy
{
public:
	static Exterminator * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyExterminator;

private:
	Exterminator(ValueMap* initProperties);
	~Exterminator();
};
