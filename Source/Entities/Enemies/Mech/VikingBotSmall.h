#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class VikingBotSmall : public Enemy
{
public:
	static VikingBotSmall * create();

private:
	VikingBotSmall();
	~VikingBotSmall();
};
