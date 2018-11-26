#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Osiris : public PlatformerEnemy
{
public:
	static Osiris* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyOsiris;

private:
	Osiris(ValueMap* initProperties);
	~Osiris();
};
