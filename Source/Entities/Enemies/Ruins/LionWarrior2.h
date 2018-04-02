#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class LionWarrior2 : public Enemy
{
public:
	static LionWarrior2 * create();

private:
	LionWarrior2();
	~LionWarrior2();
};
