#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class SkeletonCleaver : public Enemy
{
public:
	static SkeletonCleaver * create();

private:
	SkeletonCleaver();
	~SkeletonCleaver();
};
