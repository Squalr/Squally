#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Undead : public Enemy
{
public:
	static Undead * create();

	static const std::string KeyEnemyUndead;

private:
	Undead();
	~Undead();
};
