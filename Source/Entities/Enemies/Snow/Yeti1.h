#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Yeti1 : public Enemy
{
public:
	static Yeti1 * create();

private:
	Yeti1();
	~Yeti1();
};
