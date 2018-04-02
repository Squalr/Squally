#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossKrampus : public Enemy
{
public:
	static BossKrampus * create();

private:
	BossKrampus();
	~BossKrampus();
};
