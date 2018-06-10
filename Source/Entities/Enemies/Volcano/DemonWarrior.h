#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonWarrior : public Enemy
{
public:
	static DemonWarrior * create();

private:
	DemonWarrior();
	~DemonWarrior();
};
