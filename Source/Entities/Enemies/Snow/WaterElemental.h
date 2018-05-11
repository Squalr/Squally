#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class WaterElemental : public Enemy
{
public:
	static WaterElemental * create();

private:
	WaterElemental();
	~WaterElemental();
};
