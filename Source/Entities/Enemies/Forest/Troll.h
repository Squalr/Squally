#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Troll : public Enemy
{
public:
	static Troll * create();

private:
	Troll();
	~Troll();
};
