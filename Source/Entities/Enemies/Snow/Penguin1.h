#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Penguin1 : public Enemy
{
public:
	static Penguin1 * create();

private:
	Penguin1();
	~Penguin1();
};
