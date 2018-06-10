#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonWarrior : public Enemy
{
public:
	static SkeletonWarrior * create();

private:
	SkeletonWarrior();
	~SkeletonWarrior();
};
