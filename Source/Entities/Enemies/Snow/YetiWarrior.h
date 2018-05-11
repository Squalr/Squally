#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class YetiWarrior : public Enemy
{
public:
	static YetiWarrior * create();

private:
	YetiWarrior();
	~YetiWarrior();
};
