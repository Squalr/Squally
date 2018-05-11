#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Yeti : public Enemy
{
public:
	static Yeti * create();

private:
	Yeti();
	~Yeti();
};
