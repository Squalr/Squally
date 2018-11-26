#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Centaur : public PlatformerEnemy
{
public:
	static Centaur* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyCentaur;

private:
	Centaur(ValueMap* initProperties);
	~Centaur();
};
