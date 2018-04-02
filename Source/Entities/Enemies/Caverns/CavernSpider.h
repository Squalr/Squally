#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class CavernSpider : public Enemy
{
public:
	static CavernSpider * create();

private:
	CavernSpider();
	~CavernSpider();
};
