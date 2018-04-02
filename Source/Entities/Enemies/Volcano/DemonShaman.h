#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class DemonShaman : public Enemy
{
public:
	static DemonShaman * create();

private:
	DemonShaman();
	~DemonShaman();
};
