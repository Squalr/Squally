#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class Snowman : public Enemy
{
public:
	static Snowman * create();

private:
	Snowman();
	~Snowman();
};
