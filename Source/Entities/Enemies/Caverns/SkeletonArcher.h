#pragma once
#include "cocos2d.h"

#include "Entities/Enemy.h"
#include "Resources.h"

using namespace cocos2d;

class SkeletonArcher : public Enemy
{
public:
	static SkeletonArcher * create();

private:
	SkeletonArcher();
	~SkeletonArcher();
};
