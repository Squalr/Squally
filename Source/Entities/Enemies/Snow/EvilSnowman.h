#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class EvilSnowman : public Enemy
{
public:
	static EvilSnowman * create();

	static const std::string KeyEnemyEvilSnowman;

private:
	EvilSnowman();
	~EvilSnowman();
};
