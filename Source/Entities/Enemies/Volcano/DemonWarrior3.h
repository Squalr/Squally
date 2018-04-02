#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class DemonWarrior3 : public Enemy
{
public:
	static DemonWarrior3 * create();

private:
	DemonWarrior3();
	~DemonWarrior3();
};
