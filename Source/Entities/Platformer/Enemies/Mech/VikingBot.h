#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources.h"

using namespace cocos2d;

class VikingBot : public PlatformerEnemy
{
public:
	static VikingBot * deserialize(ValueMap* initProperties);

	static const std::string KeyEnemyVikingBot;

private:
	VikingBot(ValueMap* initProperties);
	~VikingBot();
};
