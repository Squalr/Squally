#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class YetiWarrior : public Enemy
{
public:
	static YetiWarrior * create();

private:
	YetiWarrior();
	~YetiWarrior();
};
