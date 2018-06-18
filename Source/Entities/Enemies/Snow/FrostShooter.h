#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class FrostShooter : public Enemy
{
public:
	static FrostShooter * create();

	static const std::string KeyEnemyFrostShooter;

private:
	FrostShooter();
	~FrostShooter();
};
