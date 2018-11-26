#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Shaman : public PlatformerEnemy
{
public:
	static Shaman * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyShaman;

private:
	Shaman(ValueMap* initProperties);
	~Shaman();
};
