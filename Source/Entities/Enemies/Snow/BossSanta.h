#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossSanta : public Enemy
{
public:
	static BossSanta * create();

private:
	BossSanta();
	~BossSanta();
};
