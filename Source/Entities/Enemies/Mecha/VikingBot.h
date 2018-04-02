#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class VikingBot : public Enemy
{
public:
	static VikingBot * create();

private:
	VikingBot();
	~VikingBot();
};
