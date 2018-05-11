#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Zombie : public Enemy
{
public:
	static Zombie * create();

private:
	Zombie();
	~Zombie();
};
