#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class RedDragon1 : public Enemy
{
public:
	static RedDragon1 * create();

private:
	RedDragon1();
	~RedDragon1();
};
