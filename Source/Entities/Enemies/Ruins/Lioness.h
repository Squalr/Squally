#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Lioness : public Enemy
{
public:
	static Lioness * create();

private:
	Lioness();
	~Lioness();
};
