#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Enemy.h"

using namespace cocos2d;

class SkeletonBaron : public Enemy
{
public:
	static SkeletonBaron * create();

private:
	SkeletonBaron();
	~SkeletonBaron();
};
