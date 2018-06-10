#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class TikiWarrior : public Enemy
{
public:
	static TikiWarrior * create();

private:
	TikiWarrior();
	~TikiWarrior();
};
