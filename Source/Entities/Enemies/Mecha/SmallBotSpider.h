#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class SmallBotSpider : public Enemy
{
public:
	static SmallBotSpider * create();

private:
	SmallBotSpider();
	~SmallBotSpider();
};
