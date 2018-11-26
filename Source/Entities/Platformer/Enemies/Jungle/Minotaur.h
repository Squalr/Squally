#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class Minotaur : public PlatformerEnemy
{
public:
	static Minotaur* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyMinotaur;

private:
	Minotaur(ValueMap* initProperties);
	~Minotaur();
};
