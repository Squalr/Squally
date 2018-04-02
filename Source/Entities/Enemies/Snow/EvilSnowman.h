#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class EvilSnowman : public Enemy
{
public:
	static EvilSnowman * create();

private:
	EvilSnowman();
	~EvilSnowman();
};
