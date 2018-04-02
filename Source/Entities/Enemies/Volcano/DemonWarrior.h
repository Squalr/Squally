#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class DemonWarrior : public Enemy
{
public:
	static DemonWarrior * create();

private:
	DemonWarrior();
	~DemonWarrior();
};
