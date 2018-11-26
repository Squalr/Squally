#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEnemy.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

class VikingBotSmall : public PlatformerEnemy
{
public:
	static VikingBotSmall* deserialize(ValueMap* initProperties);

	static const std::string MapKeyEnemyVikingBotSmall;

private:
	VikingBotSmall(ValueMap* initProperties);
	~VikingBotSmall();
};
