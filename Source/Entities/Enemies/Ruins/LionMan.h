#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class LionMan : public Enemy
{
public:
	static LionMan * create();

private:
	LionMan();
	~LionMan();
};
