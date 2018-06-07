#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossKrampus : public Enemy
{
public:
	static BossKrampus * create();

private:
	BossKrampus();
	~BossKrampus();
};
