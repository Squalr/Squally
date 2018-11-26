#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Cyclops : public PlatformerEnemy
{
public:
	static Cyclops* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyCyclops;

private:
	Cyclops(ValueMap* initProperties);
	~Cyclops();
};
