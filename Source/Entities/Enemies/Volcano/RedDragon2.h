#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class RedDragon2 : public Enemy
{
public:
	static RedDragon2 * create();

private:
	RedDragon2();
	~RedDragon2();
};
