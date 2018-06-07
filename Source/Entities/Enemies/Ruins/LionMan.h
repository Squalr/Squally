#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class LionMan : public Enemy
{
public:
	static LionMan * create();

private:
	LionMan();
	~LionMan();
};
