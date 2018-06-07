#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BatDemon : public Enemy
{
public:
	static BatDemon * create();

private:
	BatDemon();
	~BatDemon();
};
