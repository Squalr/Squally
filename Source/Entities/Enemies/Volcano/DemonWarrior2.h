#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class DemonWarrior2 : public Enemy
{
public:
	static DemonWarrior2 * create();

private:
	DemonWarrior2();
	~DemonWarrior2();
};
