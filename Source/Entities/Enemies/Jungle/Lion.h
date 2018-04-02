#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Lion : public Enemy
{
public:
	static Lion * create();

private:
	Lion();
	~Lion();
};
