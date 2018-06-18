#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Troll : public Enemy
{
public:
	static Troll * create();

	static const std::string KeyEnemyTroll;

private:
	Troll();
	~Troll();
};
