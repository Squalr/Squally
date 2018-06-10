#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class EvilSnowman : public Enemy
{
public:
	static EvilSnowman * create();

private:
	EvilSnowman();
	~EvilSnowman();
};
