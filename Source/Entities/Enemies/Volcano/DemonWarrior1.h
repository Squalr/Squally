#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class DemonWarrior1 : public Enemy
{
public:
	static DemonWarrior1 * create();

private:
	DemonWarrior1();
	~DemonWarrior1();
};
