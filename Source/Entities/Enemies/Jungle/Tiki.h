#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Tiki : public Enemy
{
public:
	static Tiki * create();

private:
	Tiki();
	~Tiki();
};
