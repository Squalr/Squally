#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossEgyptianGoddess : public Enemy
{
public:
	static BossEgyptianGoddess * create();

private:
	BossEgyptianGoddess();
	~BossEgyptianGoddess();
};
