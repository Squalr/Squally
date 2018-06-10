#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class FrostShooter : public Enemy
{
public:
	static FrostShooter * create();

private:
	FrostShooter();
	~FrostShooter();
};
