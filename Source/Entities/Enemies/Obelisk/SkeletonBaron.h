#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonBaron : public Enemy
{
public:
	static SkeletonBaron * create();

private:
	SkeletonBaron();
	~SkeletonBaron();
};
