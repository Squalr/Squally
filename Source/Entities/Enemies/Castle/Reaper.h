#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Reaper : public Enemy
{
public:
	static Reaper * create();

private:
	Reaper();
	~Reaper();
};
