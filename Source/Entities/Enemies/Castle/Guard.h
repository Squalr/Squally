#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Guard : public Enemy
{
public:
	static Guard * create();

private:
	Guard();
	~Guard();
};
