#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class TigerWarrior2 : public Enemy
{
public:
	static TigerWarrior2 * create();

private:
	TigerWarrior2();
	~TigerWarrior2();
};
