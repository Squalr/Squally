#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class AnubisWarrior : public Enemy
{
public:
	static AnubisWarrior * create();

private:
	AnubisWarrior();
	~AnubisWarrior();
};
