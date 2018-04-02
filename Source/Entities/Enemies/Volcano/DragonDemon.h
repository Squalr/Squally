#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class DragonDemon : public Enemy
{
public:
	static DragonDemon * create();

private:
	DragonDemon();
	~DragonDemon();
};
