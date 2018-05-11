#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class FrostShooter : public Enemy
{
public:
	static FrostShooter * create();

private:
	FrostShooter();
	~FrostShooter();
};
