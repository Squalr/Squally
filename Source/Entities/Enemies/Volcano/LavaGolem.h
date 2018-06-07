#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class LavaGolem : public Enemy
{
public:
	static LavaGolem * create();

private:
	LavaGolem();
	~LavaGolem();
};
