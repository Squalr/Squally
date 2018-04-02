#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class LionWarrior : public Enemy
{
public:
	static LionWarrior * create();

private:
	LionWarrior();
	~LionWarrior();
};
