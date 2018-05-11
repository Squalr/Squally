#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossEvilEye : public Enemy
{
public:
	static BossEvilEye * create();

private:
	BossEvilEye();
	~BossEvilEye();
};
