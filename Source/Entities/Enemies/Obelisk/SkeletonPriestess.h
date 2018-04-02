#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class SkeletonPriestess : public Enemy
{
public:
	static SkeletonPriestess * create();

private:
	SkeletonPriestess();
	~SkeletonPriestess();
};
