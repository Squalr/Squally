#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class ForestGolem : public Enemy
{
public:
	static ForestGolem * create();

private:
	ForestGolem();
	~ForestGolem();
};
