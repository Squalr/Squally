#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class VikingBot : public Enemy
{
public:
	static VikingBot * create();

	static const std::string KeyEnemyVikingBot;

private:
	VikingBot();
	~VikingBot();
};
