#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Undead : public Enemy
{
public:
	static Undead * create();

private:
	Undead();
	~Undead();
};
