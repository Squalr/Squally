#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Reaper : public Enemy
{
public:
	static Reaper * create();

private:
	Reaper();
	~Reaper();
};
