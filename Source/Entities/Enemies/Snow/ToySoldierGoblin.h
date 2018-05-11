#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class ToySoldierGoblin : public Enemy
{
public:
	static ToySoldierGoblin * create();

private:
	ToySoldierGoblin();
	~ToySoldierGoblin();
};
