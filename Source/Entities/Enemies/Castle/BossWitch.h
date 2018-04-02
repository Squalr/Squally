#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossWitch : public Enemy
{
public:
	static BossWitch * create();

private:
	BossWitch();
	~BossWitch();
};
