#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class Harpy : public PlatformerEnemy
{
public:
	static Harpy * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyHarpy;

private:
	Harpy(ValueMap* initProperties);
	~Harpy();
};
