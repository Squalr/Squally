#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Penguin2 : public Enemy
{
public:
	static Penguin2 * create();

private:
	Penguin2();
	~Penguin2();
};
