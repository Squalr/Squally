#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class FrostDragon : public Enemy
{
public:
	static FrostDragon * create();

private:
	FrostDragon();
	~FrostDragon();
};
