#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Gorilla : public PlatformerEnemy
{
public:
	static Gorilla* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyGorilla;

private:
	Gorilla(ValueMap* initProperties);
	~Gorilla();
};
