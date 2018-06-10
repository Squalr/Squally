#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class BossRhinoman : public Enemy
{
public:
	static BossRhinoman * create();

private:
	BossRhinoman();
	~BossRhinoman();
};
