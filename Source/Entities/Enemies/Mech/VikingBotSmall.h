#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class VikingBotSmall : public Enemy
{
public:
	static VikingBotSmall * create();

private:
	VikingBotSmall();
	~VikingBotSmall();
};
