#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class JungleDragon : public Enemy
{
public:
	static JungleDragon * create();

private:
	JungleDragon();
	~JungleDragon();
};
