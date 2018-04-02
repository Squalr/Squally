#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class DarkDragon : public Enemy
{
public:
	static DarkDragon * create();

private:
	DarkDragon();
	~DarkDragon();
};
