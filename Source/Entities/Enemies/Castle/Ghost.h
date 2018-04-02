#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Ghost : public Enemy
{
public:
	static Ghost * create();

private:
	Ghost();
	~Ghost();
};
