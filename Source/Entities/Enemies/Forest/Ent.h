#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Ent : public Enemy
{
public:
	static Ent * create();

	static const std::string KeyEnemyEnt;

private:
	Ent();
	~Ent();
};
