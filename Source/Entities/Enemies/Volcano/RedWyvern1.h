#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class RedWyvern1 : public Enemy
{
public:
	static RedWyvern1 * create();

private:
	RedWyvern1();
	~RedWyvern1();
};
