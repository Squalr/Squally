#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossRhinoman : public Enemy
{
public:
	static BossRhinoman * create();

private:
	BossRhinoman();
	~BossRhinoman();
};
