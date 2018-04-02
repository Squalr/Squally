#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Troll : public Enemy
{
public:
	static Troll * create();

private:
	Troll();
	~Troll();
};
