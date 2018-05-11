#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BossDragonOrcKing : public Enemy
{
public:
	static BossDragonOrcKing * create();

private:
	BossDragonOrcKing();
	~BossDragonOrcKing();
};
