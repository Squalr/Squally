#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class Harpy : public Enemy
{
public:
	static Harpy * create();

	static const std::string KeyEnemyHarpy;

private:
	Harpy();
	~Harpy();
};
