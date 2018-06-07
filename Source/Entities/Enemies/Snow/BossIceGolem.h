#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossIceGolem : public Enemy
{
public:
	static BossIceGolem * create();

private:
	BossIceGolem();
	~BossIceGolem();
};
