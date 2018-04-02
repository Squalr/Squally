#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Yeti2 : public Enemy
{
public:
	static Yeti2 * create();

private:
	Yeti2();
	~Yeti2();
};
