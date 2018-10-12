#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Zombie : public PlatformerEnemy
{
public:
	static Zombie * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyZombie;

private:
	Zombie(ValueMap* initProperties);
	~Zombie();
};
