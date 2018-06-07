#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class DemonDragon : public Enemy
{
public:
	static DemonDragon * create();

private:
	DemonDragon();
	~DemonDragon();
};
