#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonPriestess : public Enemy
{
public:
	static SkeletonPriestess * create();

private:
	SkeletonPriestess();
	~SkeletonPriestess();
};
