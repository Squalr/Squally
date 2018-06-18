#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Lioness : public Enemy
{
public:
	static Lioness * create();

	static const std::string KeyEnemyLioness;

private:
	Lioness();
	~Lioness();
};
