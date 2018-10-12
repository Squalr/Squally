#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Barbarian : public PlatformerEnemy
{
public:
	static Barbarian * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyBarbarian;

private:
	Barbarian(ValueMap* initProperties);
	~Barbarian();
};
