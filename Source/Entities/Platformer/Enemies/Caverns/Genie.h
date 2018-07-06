#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Genie : public PlatformerEnemy
{
public:
	static Genie * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyGenie;

private:
	Genie(ValueMap* initProperties);
	~Genie();
};
