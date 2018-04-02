#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class AnubisWarrior : public Enemy
{
public:
	static AnubisWarrior * create();

private:
	AnubisWarrior();
	~AnubisWarrior();
};
