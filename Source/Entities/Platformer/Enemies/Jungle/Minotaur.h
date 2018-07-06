#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Minotaur : public PlatformerEnemy
{
public:
	static Minotaur * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyMinotaur;

private:
	Minotaur(ValueMap* initProperties);
	~Minotaur();
};
