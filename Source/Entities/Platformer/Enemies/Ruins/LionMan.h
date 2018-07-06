#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class LionMan : public PlatformerEnemy
{
public:
	static LionMan * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyLionMan;

private:
	LionMan(ValueMap* initProperties);
	~LionMan();
};
