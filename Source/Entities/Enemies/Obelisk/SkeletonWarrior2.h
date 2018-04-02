#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class SkeletonWarrior2 : public Enemy
{
public:
	static SkeletonWarrior2 * create();

private:
	SkeletonWarrior2();
	~SkeletonWarrior2();
};
