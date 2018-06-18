#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class VikingBotSmall : public Enemy
{
public:
	static VikingBotSmall * create();

	static const std::string KeyEnemyVikingBotSmall;

private:
	VikingBotSmall();
	~VikingBotSmall();
};
