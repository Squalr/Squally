#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class BigHandsBot : public Enemy
{
public:
	static BigHandsBot * create();

private:
	BigHandsBot();
	~BigHandsBot();
};
