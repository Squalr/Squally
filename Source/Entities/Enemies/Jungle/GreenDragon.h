#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class GreenDragon : public Enemy
{
public:
	static GreenDragon * create();

private:
	GreenDragon();
	~GreenDragon();
};
