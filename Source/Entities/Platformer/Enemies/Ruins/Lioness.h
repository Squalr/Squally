#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Lioness : public PlatformerEnemy
{
public:
	static Lioness * deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyLioness;

private:
	Lioness(ValueMap* initProperties);
	~Lioness();
};
