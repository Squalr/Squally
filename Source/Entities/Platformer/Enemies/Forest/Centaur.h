#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Centaur : public PlatformerEnemy
{
public:
	static Centaur * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyCentaur;

private:
	Centaur(ValueMap* initProperties);
	~Centaur();
};
