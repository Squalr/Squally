#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class FrostDragon : public Enemy
{
public:
	static FrostDragon * create();

private:
	FrostDragon();
	~FrostDragon();
};
