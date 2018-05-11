#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossDemonKing : public Enemy
{
public:
	static BossDemonKing * create();

private:
	BossDemonKing();
	~BossDemonKing();
};
