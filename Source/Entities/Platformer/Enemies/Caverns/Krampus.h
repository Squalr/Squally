#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Krampus : public PlatformerEnemy
{
public:
	static Krampus * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyKrampus;

private:
	Krampus(ValueMap* initProperties);
	~Krampus();
};
