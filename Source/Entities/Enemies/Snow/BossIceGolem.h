#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossIceGolem : public Enemy
{
public:
	static BossIceGolem * create();

private:
	BossIceGolem();
	~BossIceGolem();
};
