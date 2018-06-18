#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Zombie : public Enemy
{
public:
	static Zombie * create();

	static const std::string KeyEnemyZombie;

private:
	Zombie();
	~Zombie();
};
