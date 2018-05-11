#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class SkeletonMage : public Enemy
{
public:
	static SkeletonMage * create();

private:
	SkeletonMage();
	~SkeletonMage();
};
