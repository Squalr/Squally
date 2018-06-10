#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class ToySoldierGoblin : public Enemy
{
public:
	static ToySoldierGoblin * create();

private:
	ToySoldierGoblin();
	~ToySoldierGoblin();
};
