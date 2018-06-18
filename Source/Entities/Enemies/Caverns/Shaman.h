#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Shaman : public Enemy
{
public:
	static Shaman * create();

	static const std::string KeyEnemyShaman;

private:
	Shaman();
	~Shaman();
};
