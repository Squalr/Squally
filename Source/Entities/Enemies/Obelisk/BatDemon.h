#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BatDemon : public Enemy
{
public:
	static BatDemon * create();

private:
	BatDemon();
	~BatDemon();
};
