#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Tigress : public Enemy
{
public:
	static Tigress * create();

private:
	Tigress();
	~Tigress();
};
